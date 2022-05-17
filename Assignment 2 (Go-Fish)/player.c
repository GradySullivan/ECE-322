#include <stdio.h>
#include "player.h"
#include <string.h>
#include <stdbool.h>
#include <time.h>


/*int main()
{
	return 0;
}*/


int add_card(struct player* target, struct card* new_card)
{
	// allocate space
	struct hand* temp;
	temp = (struct hand*)malloc(sizeof(struct hand*));
	if (temp == NULL) { return -1; };
	// initialize new element
	temp->top = *new_card;
	temp->next = target->card_list;
	//set list to temp, new front
	target->card_list = temp;	
	return 0;
}


int compare_cards(struct card* card1, struct card* card2)
{
	char suit1 = card1->suit;
	char suit2 = card2->suit;
	char rank1 = card1->rank[0];
	char rank2 = card2->rank[0];

	if((suit1 == suit2) && (rank1 == rank2))
		{return 1;}
	else
		{return 0;}
}


int remove_card(struct player* target, struct card* old_card)
{
	struct hand* curNode = target->card_list;
	struct hand* prevNode = NULL;
	if(curNode == NULL)
		return 1;
	int same = compare_cards(&(curNode->top), old_card);
	//if(same == 1)
		//prevNode = (struct hand*)malloc(sizeof(struct hand*));	
	while(same == 0)
	{	
		prevNode = curNode;
		curNode = curNode->next;
		same = compare_cards(&(curNode->top), old_card);
		if(curNode == NULL)
			return 1;
	} 
	if (prevNode != NULL)
		prevNode->next = curNode->next;
	else
		target->card_list = curNode->next;
	free(curNode);
	return 0;
}


// ---------- for check_add_book ----------
int get_hand_size(struct player* target)
{
	int count = 0;
	struct hand* temp;
	temp = target->card_list;
	while (temp != NULL){
		count++;
		temp = temp->next;
	}
	return count;
}
int countOccurrences(char arr[], int arrlen, char x){
	int res = 0;
	for (int i=0; i<arrlen; i++)
		if (x == arr[i])
			res++;
	return res;
}
char check_add_book(struct player* target)
{

	// get hand size and create array of same size
	int n = get_hand_size(target);
	char arr[n];

	// initialize stuff
	int i = 0;
	struct hand* temp;
	struct hand* temp1;
	temp = target->card_list;
	temp1 = target->card_list;
	
	// add ranks to list
	while (temp != NULL){
		arr[i] = (&(temp->top))->rank[0];
		i++;
		temp = temp->next;
	}

	// Check number of Occurances of ranks
	for (int j = 0; j < (sizeof(arr)/sizeof(arr[0])); j++){
		int occ = countOccurrences(arr, n, arr[j]);
		if (occ == 4){
			// remove every card
			if(target == &user){
				if(arr[j] == '1')
					printf("\n\t-Player 1 books %c0", arr[j]);
				else
					printf("\n\t-Player 1 books %c", arr[j]);}
			else{
				if(arr[j] == '1')
					printf("\n\t-Player 2 books %c0", arr[j]);
				else
					printf("\n\t-Player 2 books %c", arr[j]);}
			while (temp1 != NULL){
				if ((&(temp1->top))->rank[0] == arr[j])// should be users hand					
					remove_card(target, &(temp1->top));
				temp1 = temp1->next;
			}
			// place rank into book
			for (int k = 0; k < (sizeof(target->book)/sizeof(target->book[0])); k++){
				if (target->book[k] == '0')
				{
					target->book[k] = arr[j];
					break;
				}
			}
			return arr[j]; // only 1 set of 4 at a time*/
			
			// go through linked list of hand
			// if card rank == arr[j]
				//remove card
			// add rank to book	
		}	
	}
	return 0;
}



int search(struct player* target, char rank)
{
	struct hand* temp;

	temp = target->card_list;
	while (temp != NULL){
		if (rank == (&(temp->top))->rank[0]){
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}


int transfer_cards(struct player* src, struct player* dest, char rank)
{
	//struct hand* hand1Node = src->card_list;
	//struct hand* hand2Node = dest->card_list;
	struct hand* hand1Node;
	//struct hand* hand2Node;
	hand1Node = src->card_list;
	//hand2Node = dest->card_list;
	while(hand1Node != NULL)
		{
		if((&(hand1Node->top))->rank[0] == rank)
		{
			add_card(dest, &(hand1Node->top));			
			remove_card(src, &(hand1Node->top));	
		}
		hand1Node = hand1Node->next;
		}
	return 0;
}


int game_over(struct player* target)
{
	if(target->book[6] == '0')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


int reset_player(struct player* target)
{
	struct hand* temp;
	temp = target->card_list;
	char zero = '0';
	while(temp != NULL)
	{
		remove_card(target, &(temp->top));
		temp = temp->next;
	}
	// Re-Initialize Book
	for (int i = 0; i < 7; i++){
		target->book[i] = zero;}
	return 0;
}



char computer_play(struct player* target)
{
	char choice[13][4] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	srand(time(0));
	while(1)
	{
		int index;
		index  = rand() % 13;
		struct hand* node = target->card_list;
		while(node != NULL)
		{
			if(strcmp((node->top).rank, choice[index]) != 0)
			{
				return (node->top).rank[0];
			}
			else
			{
				node = node->next;
			}
		}
	}
}


char user_play(struct player* target)
{
	while(1)
	{
		char asking;
		printf("\nPlayer 1's turn, enter a Rank: ");
		scanf("%c", &asking);
		while((getchar()) != '\n');
		struct hand* node;
		node = target->card_list;
		while(node != NULL)
		{
			if((&(node->top))->rank[0] == asking)
			{
				return (node->top).rank[0];
			}
			else
			{
				node = node->next;
			}
		}
		printf("Error - must have at least one card from rank to play \n\n");
	}
return 0;
}
