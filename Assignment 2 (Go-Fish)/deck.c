#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "time.h"
#include "player.h"
#include <string.h>

/*int main()
{
	shuffle();
	int size = deck_size();
	printf("size = %d\n", size);
	
}*/


int shuffle(){
	memset(deck_instance.list, 0, sizeof(deck_instance.list));
	// card suits and values
	char suits[4] = {'C','D','H','S'};
	char value[13][100] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	
	// ----- Initialize the deck -----
	int card_count = 0;
	for (int a = 1; a < 14; a++){
		if(a==10)
			deck_instance.list[card_count].rank[1] = '0';
		for (int b = 1; b < 5; b++){
			if(a==10)
				deck_instance.list[card_count].rank[1] = '0';
			deck_instance.list[card_count].rank[0] = value[a-2][100];			
			deck_instance.list[card_count].suit = suits[b-1];		
			card_count += 1;
		}
	}

	// ----- Shuffle -----
	srand(time(NULL));
	int i;
	struct deck temp;
	for(i=0;i<52;i++)
	{
		int j = rand() % (i+1);
		temp.list[i] = deck_instance.list[i];
		deck_instance.list[i] = deck_instance.list[j];
		deck_instance.list[j] = temp.list[i];
	}

	return 0;
}


int swap(struct card a, struct card b)
{
	struct card temp = a;
	a = b;
	b = temp;
	return 0;
}


int deal_player_cards(struct player* target){
	
	srand(time(NULL));
	int j;
	for(j = 0; j < 52; j++)
	{
		int k = rand() % (j+1);
		swap(deck_instance.list[j], deck_instance.list[k]);
	}
	int i = 0;
	char dealt = 'X';
	int counter = 0;
	while(counter < 7)
	{
		if(deck_instance.list[i].suit != dealt)
		{
			add_card(target, &((&deck_instance)->list[i]));
			deck_instance.list[i].suit = dealt;
			counter++;
		}
		i++;
	}
	return 0;
}


size_t deck_size()
{
	int i = 0;
	int size = 0;
	char blank = 'X';
	while(i < 52)
	{
		if(deck_instance.list[i].suit != blank)
			size++;
			i++;
	}
	return size;
}

struct card* next_card()
{
	struct card* temp;
	for(int i = 0; i < 52; i++)
	{
		if(deck_instance.list[i].suit == 'X')
		{
			continue;
		}
		else{
			temp = &((&deck_instance)->list[i]);
			return temp;
		}
	}
	return NULL; //empty if NULL
}
	
