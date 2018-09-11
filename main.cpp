/*Final Project Submission
Name: Lok Hong Sum */

#include "stdafx.h"

#include "player.h"
#include "deck.h"
#include "card.h"
#include "func.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
	cout << "Welcome to modified Big2 game" <<endl;
	cout << "Your objective is to be the first to discard your entire hand. Diamond 3 starts first." << endl;
	cout<<"You may only discard a higher valued single or pair of cards depending on the last card /s discarded."<<endl;
	
	/*Create human player and CPU player objects. Display all names and points*/
	Player_profile human_profile;
	human_profile.set_name(0);
	Player_profile CPU1_profile;
	CPU1_profile.set_name(1);
	Player_profile CPU2_profile;
	CPU2_profile.set_name(2);
	Player_profile CPU3_profile;
	CPU3_profile.set_name(3);
	
	cout << "Hi " << human_profile.get_name()<< "! You will be playing against: " <<endl;
	cout << CPU1_profile.get_name() <<endl;
	cout << CPU2_profile.get_name() <<endl;
	cout << CPU3_profile.get_name() <<endl;
	
	cout<< "Starting game";
	pause(3); //call pause function for 3s
	cout<<endl;
	
	/*Create Card object*/
	Card card;

	/*Create deck object*/
	Deck deck;

	/*For testing: View deck
	deck.display();
	system("PAUSE");*/
	
	/*Deal into 4 hands*/
	deck.deal_hand();
	cout<<"Dealing Cards to players..";
	pause(3);
	cout<<endl;
	
	/*Find starting player*/
	player_turn = deck.find_starting();

	cout<<endl<<"Diamond 3 is with "<<player_turn_s[player_turn]<<". "<< player_turn_s[player_turn]<<" will start first."<<endl<<endl;

	/* Store game winner*/
	Player_Id game=NIL;

	/**Game start**/
	
	while(true)
	{
		/*check game winning condition*/
		game=deck.game_win();

		if(game!=NIL)
		{
			cout<<"Game ended"<< endl<<player_turn_s[game]<< " is the winner."<<endl<<endl;
			break;
		}
			
		cout << endl<<"~~ "<<player_turn_s[player_turn]<<"'s turn ~~"<<endl; //show which turn
			
		/*If Player's turn*/
		if(player_turn==Player)
		{		
			deck.display_player();	//show player hand
			if(turn_num==0) //if 1st round, show only 1 and 2 discard options. (ie cannot skip)
			{
				if(user_inputs(12, deck.player_hand)==-1) 
					continue; //if invalid input
			}
			else if (turn_num!=0) // if not 1st round, show options depending on pile type
			{
				if(pile_owner==Player) //if pile owner is player, display all options (ie all others skipped prior to this)
				{
					if(user_inputs(123, deck.player_hand)==-1)
					continue;
				}
					
				else if(pile_owner!=Player) //If pile owner is not player. Player must discard according to pile type or skip.
				{
					if(pile_type==Single) //pile type is single card
					{
						if(user_inputs(13, deck.player_hand)==-1)
						continue;
					}
					else if (pile_type ==Pair)//pile type is pair
					{
						if(user_inputs(23, deck.player_hand)==-1)
						continue;
					}
				}			
			}
	
		}
		
		/*If CPU turn*/
		if(player_turn!=Player)	
		{					
			if(player_turn==CPU1)
			{
				CPU_play(deck.CPU1_hand,CPU1); //call CPU play function
				//deck.display_CPU1(); //show CPU1 hand for testing
				cout<<"CPU1: "<<deck.cardsnum(CPU1)<<" cards left"<<endl; //show number of cards left in hand
			}
			
			else if(player_turn==CPU2)
			{
				CPU_play(deck.CPU2_hand,CPU2); //call CPU play function
				//deck.display_CPU2(); //show CPU2 hand for testing 
				cout<<"CPU2: "<<": "<<deck.cardsnum(CPU2)<<" cards left"<<endl;
			}
			
			else if(player_turn==CPU3)
			{
				CPU_play(deck.CPU3_hand,CPU3); //call CPU play function
				//deck.display_CPU3(); //show CPU3 hand for testing
				cout<<"CPU3: "<<": "<<deck.cardsnum(CPU3)<<" cards left"<<endl;
			}
			
			show_game_status();	 //show game status after every turn
			pause(2);
		}					
	}
	
	/*Display end game details*/
	cout<< "Score details"<<endl;

	/*Set scores according to number of cards left*/
	human_profile.set_score(deck.cardsnum(Player));
	CPU1_profile.set_score(deck.cardsnum(CPU1));
	CPU2_profile.set_score(deck.cardsnum(CPU2));
	CPU3_profile.set_score(deck.cardsnum(CPU3));
	
	/*Get scores and display*/
	cout<< "Cards left for Player: "<< human_profile.get_score()<<endl;
	cout<< "Cards left for CPU1: "<< CPU1_profile.get_score()<<endl;
	cout<< "Cards left for CPU2: "<< CPU2_profile.get_score()<<endl;
	cout<< "Cards left for CPU3: "<< CPU3_profile.get_score()<<endl;
	
	
	system("pause");
	return 0;
	
}
