#include <stdio.h>
#include "gofish.h"
#include "card.h"
#include "player.h"
#include "deck.h"
#include <stdlib.h>

void print_card(struct card* currentCard){
	if (currentCard->rank[1] != '\0') {
		printf("%c%c%c ", currentCard->rank[0], currentCard->rank[1], currentCard->suit);
	}
	else {
		printf("%c%c ", currentCard->rank[0], currentCard->suit);
	}
}	


void print_book(struct player* target)
{
	for(int i=0; i < 7; i++)
	{
		if(target->book[i] == '0')
			printf(" ");
		else
			if(target->book[i] == '1')
				printf("%c0 ", target->book[i]);
			else
				printf("%c ", target->book[i]);
	}
}

int score(struct player* target)
{
	int counter = 0;
	for(int i=0; i < 7; i++)
	{
		if(target->book[i] != '0')
			counter++;
	}
	return counter;
}


void print_hand(struct player* target){
	struct hand* tempNode;
	int i = 1;
	
	tempNode = target->card_list;
	printf("\nPlayer 1's Hand - ");
	while (tempNode != NULL){
		//printf("Current Node: (%d) ", i);
		print_card(&(tempNode->top));
		tempNode = tempNode->next;
		i++;
	}
}



struct card* removeNode(struct player* target){
	struct hand* temp;
	int i = 0;
	int rand = 4;
	temp = target->card_list;
	while (temp != NULL){
		if (rand == i){
			print_card(&(temp->top));
			break;
		}
		temp = temp->next;
		i++;
	}
	return &(temp->top);
}


//int main(int args, char* argv[]) 
int main()
{
	char rank;
	char dealt = 'X';
	char again;
	int turn = 1;

	while(1)
	{
		reset_player(&user);
		reset_player(&computer);
		printf("Shuffling deck...\n");
		shuffle();
		again = 'N';
		// deal cards initially
		deal_player_cards(&user);
		deal_player_cards(&computer);
		
		// Enter endless loop until game is over
		while(1)
		{
			while(turn == 1)
			{	
				int hand_size = get_hand_size(&user); //put get_hand in player.h
				if(hand_size == 0)
				{
					struct card* petty_card = next_card();				
					add_card(&user, petty_card);
					deck_instance.list[52-deck_size()].suit = dealt;
				}

				// user will go first
				print_hand(&user);
				printf("\nPlayer 1's Book - ");
				print_book(&user);
				printf("\nPlayer 2's Book - ");
				print_book(&computer);
				rank = user_play(&user);
			
				// check if computer has same rank or not
			
				if(search(&computer, rank) == 1)
				{
				
					printf("\t-Player 2 has ");
					struct hand* node;
					node = (&(computer))->card_list;
					while(node != NULL)
					{
						if((&(node->top))->rank[0] == rank)
							print_card(&(node->top));
						node = node->next;
					}
					transfer_cards(&computer, &user, rank);
					check_add_book(&user);	
					printf("\n\t-Player 1 gets another turn");
				}
				else
				{
					turn = 0;
					if(rank == '1')
						printf("\t-Player 2 has no %c0's", rank);
					else
						printf("\t-Player 2 has no %c's", rank);
					struct card* fishy = next_card();				
					add_card(&user, fishy);
					printf("\n\t-Go Fish, Player 1 draws ");
					print_card(fishy);
					deck_instance.list[52-deck_size()].suit = dealt;
					check_add_book(&user);	
				
				}		
				printf("\n");
				
				// check whether game is over
				if(game_over(&user) == 1)
				{
					printf("\n");
					print_hand(&user);
					printf("\nPlayer 1's Book - ");
					print_book(&user);
					printf("\nPlayer 2's Book - ");
					print_book(&computer);
					printf("\n");
					int user_score = score(&user);
					int computer_score = score(&computer);
					printf("Player 1 Wins! %d-%d\n\n", user_score, computer_score);
					while(1)
					{
						printf("Do you want to play again [Y/N]:");
						scanf("%c", &again);
						while((getchar()) != '\n');
						if(again == 'Y')
							break;
						else if(again == 'N'){
							printf("Exiting.\n");
							exit(0);}
						else
							printf("Enter 'Y' or 'N': ");
					}
					if(again == 'Y')
						break;
				}
				if(again == 'Y')
					break;
			}
			turn = 1;
			if(again == 'Y')
				break;

			while(turn == 1)
			{
				int hand_size = get_hand_size(&computer);
				if(hand_size == 0)
				{
					struct card* petty_card = next_card();				
					add_card(&computer, petty_card);
					deck_instance.list[52-deck_size()].suit = dealt;
				}
				printf("\n");
				// computer goes next
				print_hand(&user);
				printf("\nPlayer 1's Book - ");
				print_book(&user);
				printf("\nPlayer 2's Book - ");
				print_book(&computer);

				// check if computer has same rank or not
				rank = computer_play(&computer);
				if(rank == '1')
					printf("\nPlayer 2's turn, enter a Rank: %c0", rank);
				else
					printf("\nPlayer 2's turn, enter a Rank: %c", rank);
				if(search(&user, rank) == 1)
				{
				
					printf("\n\t-Player 1 has ");
					struct hand* node;
					node = (&(computer))->card_list;
					while(node != NULL)
					{
						if((&(node->top))->rank[0] == rank)
							print_card(&(node->top));
						node = node->next;
					}
					transfer_cards(&user, &computer, rank);
					check_add_book(&computer);
					printf("\n\t-Player 2 gets another turn");
				}
				else
				{
					turn = 0;
					if(rank == '1')
						printf("\n\t-Player 1 has no %c0's", rank);
					else
						printf("\n\t-Player 1 has no %c's", rank);
					struct card* fishy = next_card();				
					add_card(&computer, fishy);
					printf("\n\t-Go Fish, Player 2 draws a card");
					deck_instance.list[52-deck_size()].suit = dealt;
					check_add_book(&computer);
				}
				
				printf("\n");
			
				// check whether game is over
				if(game_over(&computer) == 1)
				{
					printf("\n");
					print_hand(&user);
					printf("\nPlayer 1's Book - ");
					print_book(&user);
					printf("\nPlayer 2's Book - ");
					print_book(&computer);
					printf("\n");
					int user_score = score(&user);
					int computer_score = score(&computer);
					printf("Player 2 Wins! %d-%d\n\n", computer_score, user_score);

					while(1)
					{
						printf("Do you want to play again [Y/N]:");
						scanf("%c", &again);
						while((getchar()) != '\n');
						if(again == 'Y')
							break;
						else if(again == 'N'){
							printf("Exiting.\n");
							exit(0);}
						else
							printf("Enter 'Y' or 'N': ");
					}
					
				}
				if(again == 'Y')
					break;
			}
			turn = 1;
			if(again == 'Y')
				break;

		}
		
	}
	return 0;

}


