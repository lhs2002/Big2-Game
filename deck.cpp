#include "stdafx.h"

#include <vector>
#include <ctime>
#include <iostream>
#include "deck.h"
#include "card.h"

using namespace std;

/*Default constructor-Create 52 unique cards and shuffle*/
Deck::Deck()
{
	/*create 52 unique cards*/
	for (int s = 0; s < 4; s++)
	{
		for (int v = 0; v <= 12; v++)
		{
			Card card(v,s);
			deck_cards.push_back(card);
		}
	}
			
			/*Activate for shuffling*/		
			srand((int)time(NULL));
			vector<Card> temp;
			int index;
		
			while (deck_cards.size() > 0)
			{
				// move a random element in deck_cards to temp
				index = rand() % deck_cards.size();
				
				temp.push_back(deck_cards.at(index));
				deck_cards.erase(deck_cards.begin() + index);
		
			}
	
			//move elements of temp (shuffled deck) into deck_cards
			while (temp.size() > 0)
			{
				deck_cards.push_back(temp.back());
				temp.pop_back();
			}
		
		
}
				
/*Display deck of cards created for checking*/
void Deck::display()
{
	cout << "(For testing) Display deck created: " <<endl;
	for (int i=0; i<52;i++)
	{
		cout << "Card " << i << ": ";
		cout << "in values: ";
		cout << deck_cards[i].rank<< " of " <<deck_cards[i].suit<<endl;
		cout << " in string: ";
		cout << deck_cards[i].display()<<endl;
	}	
}
	
/*Divide deck into 4 decks*/
void Deck::deal_hand()
{		
			
	//CPU2 hand
	for (int i = 0; i < 13; i++)
	{
		CPU2_hand.push_back(deck_cards.back());
		deck_cards.pop_back();
	}
			
	//CPU3 hand
	for (int i = 0; i < 13; i++)
	{
		CPU3_hand.push_back(deck_cards.back());
		deck_cards.pop_back();
	}
			
	//Player hand
	for (int i = 0; i < 13; i++)
	{
		player_hand.push_back(deck_cards.back());
		deck_cards.pop_back();
	}
	
	//CPU1 hand
	for (int i = 0; i < 13; i++)
	{
		CPU1_hand.push_back(deck_cards.back());
		deck_cards.pop_back();
	}
			
}
		
/*Display player hand*/
void Deck::display_player()
{
	cout << "~~Your hand~~" <<endl;
	for (int i = 0; i < player_hand.size(); i++)
	{
		cout << "Card " << i << ": ";
		//std::cout << "in values: ";
		//std::cout << player_hand[i].rank<< " of " <<player_hand[i].suit<<std::endl;
		//cout << " in string: ";
		cout << player_hand[i].display()<<endl;
	}
}
		
/*Display CPU1 hand for testing*/
void Deck::display_CPU1()
{
	cout << " CPU1's hand" <<endl;
	for (int i = 0; i < CPU1_hand.size(); i++)
	{
		cout << "Card " << i << ": ";
		//std::cout << "in values: ";
		//std::cout << CPU1_hand[i].rank<< " of " <<CPU1_hand[i].suit<<std::endl;
		//std::cout << " in string: ";
		cout << CPU1_hand[i].display()<<std::endl;
	}
}
		
/*Display CPU2 hand for testing*/
void Deck::display_CPU2()
{
	std::cout << " CPU2's hand" <<std::endl;
	for (int i = 0; i < CPU2_hand.size(); i++)
	{
		cout << "Card " << i << ": ";
		//std::cout << "in values: ";
		//std::cout << CPU2_hand[i].rank<< " of " <<CPU2_hand[i].suit<<std::endl;
		//std::cout << " in string: ";
		cout << CPU2_hand[i].display()<<endl;
	}
}
		
/*Display CPU3 hand for testing*/
void Deck::display_CPU3()
{
	cout << " CPU3's hand" <<endl;
	for (int i = 0; i < CPU3_hand.size(); i++)
	{
		cout << "Card " << i << ": ";
		//std::cout << "in values: ";
	//	std::cout << CPU3_hand[i].rank<< " of " <<CPU3_hand[i].suit<<std::endl;
		//std::cout << " in string: ";
		cout << CPU3_hand[i].display()<<endl;
	}
}
		
/*Find starting player*/
Player_Id Deck::find_starting() 
{
	int count;
			
	for (int i=0;i<13;i++)
	{
		if ((player_hand[i].rank == 0) && (player_hand[i].suit == 0))
		{
			return Player;
		}
		else if ((CPU1_hand[i].rank == 0) && (CPU1_hand[i].suit == 0))
			return CPU1;
		else if ((CPU2_hand[i].rank == 0) && (CPU2_hand[i].suit == 0))
			return CPU2;
		else if ((CPU3_hand[i].rank == 0) && (CPU3_hand[i].suit == 0))
			return CPU3;
	}	
}
		

/*Check for empty hands*/
Player_Id Deck::game_win()
{
	if(CPU1_hand.empty())
		return CPU1;
	else if(CPU2_hand.empty())
		return CPU2;
	else if(CPU3_hand.empty())
		return CPU3;
	else if(player_hand.empty())
		return Player;
	else
		return NIL;
}


/*Check no. of cards in hand*/
int Deck::cardsnum(Player_Id p)
{
	if(p== CPU1)
		return CPU1_hand.size();
	else if(p== CPU2)
		return CPU2_hand.size();
	else if(p== CPU3)
		return CPU3_hand.size();
	else return player_hand.size();	
}
