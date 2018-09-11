#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include "player.h"
#include "deck.h"
#include "card.h"
#include "func.h"

using namespace std;

/*String variables to display enum values*/
const string pile_type_s[3] = { "Single","Pair","NoCards" };
const string pile_owner_s[5] = { "Player","CPU1","CPU2","CPU3","NIL" };
const string player_turn_s[5] = { "Player", "CPU1", "CPU2", "CPU3", "NIL" };

/*Setup game to initial state*/
int turn_num = 0;
Player_Id pile_owner = NIL;
Pile pile_type = NoCards;
Player_Id player_turn = NIL;
Card pile[2] = { Card(-1,-1),Card(-1,-1) };

/*Serves 1st level menu according to main inputs and validate for correct numeric inputs. Return int to user input function*/
int menu_lvl1(int i, vector<Card> &v)
{
	string option[3]= {
		"1) Discard single card","2) Discard a pair of cards",
		"3) Skip turn"};
	
	unsigned int x;
	cout << endl<<"MENU OPTIONS"<<endl;
	switch(i)
	{
	   	case 13: //single or skip options
	    	cout << option[0]<<endl;
	    	cout << option[2]<<endl;	   
	    	x = int_checker(1,v);//check for integer input
	    	
	    	if((x ==1)||(x==3))
	    		return x;
	    	cout << "Only 1 or 3 allowed"<<endl;
			return -1;
	    
					
	    case 12: //single or pair options
	    	cout << option[0]<<endl;
	    	cout << option[1]<<endl;
	    
			x = int_checker(1,v);//check for integer input
	    	
	    	if((x ==1)||(x==2))
	    		return x;
	    	cout << "Only 1 or 2 allowed"<<endl;
	    	return -1;	
	    		
					
	   	case 23: // pair or skip options
	    	cout << option[1]<<endl;
	    	cout << option[2]<<endl;
	    
	    	x = int_checker(1,v);//check for integer input
	    	
	    	if((x ==2)||(x==3))
	    		return x;
	    	cout << "Only 2 or 3 allowed"<<endl;
	    	return -1;
	    	
					
	   	case 123: //all options
	   		cout << option[0]<<endl;
	   		cout << option[1]<<endl;
	   		cout << option[2]<<endl;
	   	
	   		x = int_checker(1,v);//check for integer input
	   		
	    	if((x ==1)||(x==2)||(x==3))
	    		return x;
	    	cout << "Only 1,2 or 3 allowed"<<endl;
	    	return -1;	
	    						
	}	
}

/* /*Displays card menu, gets card number to discard, validates and calls respective card checkers*/
int user_inputs(int x, vector<Card> &v)
{	
	
	int response = menu_lvl1(x,v);
	int single_card; //player input for single discarded card
	int pair1; //player input for 1st pair discarded card
	int pair2; //player input for 2nd pair discarded card
	
	if(response==1) //user wants to discard single card
	{
		cout << "Choose 1 card to discard: ";
		
		/*check for valid integer input*/
		single_card = int_checker(2,v);
		if(single_card==-1) //fails valid integer input
			return -1;
	
		if(singlecard_checker(single_card,v,Player)==-1) //call single card checker if integer checks successful
			return -1; 
		
	}
	else if(response==2)
	{
		cout << "Choose 1st card to discard: ";
		
		pair1 = int_checker(2,v);
		if(pair1==-1)
			return -1;
		else
		{
			cout << "Choose 2nd card to discard: ";
	
			pair2 = int_checker(2,v);
			if(pair2==-1)
				return -1;
			
			else if(pair2!=-1)
			{
				if(paircard_checker(pair1, pair2,v,Player)==-1) //call pair card checker
					return -1;
			}
				 
		}
		

	}	
	else if(response==3)
	{
		cout << "Turn skipped"<<endl;
		player_turn=CPU1;	
	}	
}

/*Check if single card selected by user is valid*/
int singlecard_checker(int single_card,vector<Card> &v, Player_Id p)
{
	/*If its 1st turn, only allow discard of diamond 3*/
	if(turn_num==0)
	{
		if((v[single_card].rank==0)&& (v[single_card].suit==0))
		{
			discard1(single_card, p,v);
		}	
			
		else
		{
			cout << "This is the first round. Can only discard Diamond 3."<<endl;
			return -1;
		}	
			
	}
	/*If not 1st turn*/
	else if (turn_num!=0)
	{
		/*Allow discard with no conditions if pile owner is player*/
		if(pile_owner==Player)
		{
			discard1(single_card, p,v);
		}
		
		/*Pile owner is not player. Only allow discard if card rank is higher and/or card suit is higher than card in discard pile*/
		else if(pile_owner!=Player)
		{
			if (v[single_card].rank > pile[0].rank)
			{
				discard1(single_card, p,v);
			}
			else if (v[single_card].rank == pile[0].rank)
			{
				if(v[single_card].suit > pile[0].suit)
				{
					discard1(single_card, p,v);
				}
				else
				{
					cout << "Suit is lower. Cannot discard." <<endl;
					return -1;
				}					
			}
			else 
			{
				cout <<"Rank is lower. Cannot discard"<<endl;
				return -1;
			}
		}		
	}
}

	
/*Check if pair cards selected by user is valid*/
int paircard_checker(int pair1, int pair2, vector<Card> &v,Player_Id p)
{
	/*checks if both cards selected are of equal rank*/
	if((v[pair1].rank)==(v[pair2].rank)) 
	{
		/*If 1st turn, only allow discard if pair contains a diamond 3*/
		if(turn_num==0)
		{
			if((v[pair1].rank==0)&& (min(v[pair1].suit,v[pair2].suit)==0))
				{
					discard2( pair1, pair2,p,v);
				}
			else
			{
				cout << "Diamond 3 is not included in pair." <<endl;
				return -1;
			}
		}
		/*If not 1st turn*/
		else if (turn_num!=0)
		{
			/*Allow discard without conditions if player owns pile*/
			if(pile_owner==Player)
			{
				discard2( pair1, pair2,p,v);
			}
			/*If pile owner is not player, only allow if rank of pair is higher than pile or if same rank, discarded pair contains highest ranked suit.*/
			else if (pile_owner!=Player)
			{
				if (v[pair1].rank > pile[0].rank)
				{
					discard2( pair1, pair2,p,v);
				}
				else if(v[pair1].rank == pile[0].rank)
				{
					if((max(v[pair1].suit,v[pair2].suit)) > (max(pile[0].suit,pile[1].suit)))
					{
							discard2( pair1, pair2,p, v);
					}
					else 
					{
						cout << "Largest suit of selected cards is smaller than pile."<<endl;
						return -1;
					}
				}
				else
				{
					cout << "Rank of selected cards smaller than pile."<<endl;
					return -1;
				}	
				
			}
				
		}
	}
	else
	{
		cout << "Ranks does not match for selected pair cards"<<endl;
		return -1;
	}
}
/*Ask for user input and check for valid input*/
int int_checker(int menu, vector<Card> &v)
{	
	unsigned int x;
	
	cin>>x;
	cout << endl;
	
	/*Check for valid inputs at card menu*/
	if(menu==2)
	{
		/*Do not allow selection of card number outside size of player's hand*/
		if(x>(v.size()-1))
		{
			cout << "Cannot select Card number outside your hand."<<endl;
			return -1;
		}
		/*If non-integers selected*/
		else if(cin.fail())
		{
			cout << "Invalid numeric selection. Choose again." <<endl;
			/*Clear stream of invalid input*/
			cin.clear();
			cin.ignore(256,'\n');	
			return -1;	
		}
		else return x;
	}

	/*Check for valid inputs at initial menu*/
	else if(menu==1)
	{
		if(cin.fail())
		{
			cout << "Invalid numeric selection. Choose again." <<endl;
			/*Clear stream of invalid input*/
			cin.clear(); //clear error flag
			cin.ignore(256,'\n'); //clear invalid characters input
			return -1;	
		}
		else return x;
	}
}

/*Discards card of specific player/CPU from associated hand*/
void discard1(int discard_card, Player_Id p, vector<Card> &v)
{
	/*Updates pile*/
	pile[0].rank=v[discard_card].rank;
	pile[0].suit=v[discard_card].suit;
	
	/*Show pile for testing*/
	//cout << "Current Pile: "<< pile[0].rank << " of " << pile[0].suit<<endl;
	
	/*Delete discarded card from hand vector*/
	v.erase(v.begin()+ discard_card);
	
	/*Increment turn number*/
	turn_num+=1;
	
	/*Update pile owner*/
	pile_owner=p;
	
	/*Update pile type*/
	pile_type = Single;
	
	/*Update player turn*/
	if(p==Player)
		player_turn=CPU1;
	else if(p==CPU1)
		player_turn=CPU2;
	else if(p==CPU2)
		player_turn=CPU3;
	else if(p==CPU3)
		player_turn=Player;
}

/*Discard pair of cards of specific player/CPU from associated hand*/
void discard2(int discard_card1,int discard_card2, Player_Id p, vector<Card> &v)
{
	/*Updates pile*/
	pile[0].rank = v[discard_card1].rank;
	pile[0].suit = v[discard_card1].suit;
	pile[1].rank = v[discard_card2].rank; 
	pile[1].suit = v[discard_card2].suit;
	
	
	/*Mark for deletion*/
	v[discard_card1].rank = 99;  
	v[discard_card1].suit = 99;
	v[discard_card2].rank = 99;  
	v[discard_card2].suit = 99;
	
	/*Iterate vector 2x and delete the marked elements*/
	int a=0;
	while(a<3)	
	{
		for(int i=0;i<v.size();i++)
		{
			if(v[i].rank==99)
			{
				v.erase(v.begin() + i);
			}
		}
		a++;
	}
	
	/*Increment turn number*/
	turn_num+=1;
	
	/*Update pile owner*/
	pile_owner=p;
	
	/*Update pile type*/
	pile_type = Pair;
	
	/*Update player turn*/
	if(p==Player)
		player_turn=CPU1;
	else if(p==CPU1)
		player_turn=CPU2;
	else if(p==CPU2)
		player_turn=CPU3;
	else player_turn=Player;
}

/*Pile information at start of every turn*/
void show_game_status()
{
	cout << endl<<"Current pile owner: "<< pile_owner_s[pile_owner]<<endl;
	cout << "Current pile type: "<< pile_type_s[pile_type]<<endl;
	if(pile_type==Single)
		cout << "Current pile: "<< pile[0].display()<<endl;
	else if(pile_type==Pair)
		cout << "Current pile: "<< pile[0].display()<< " & "<< pile[1].display()<< endl;
	else
		cout << "Current pile: "<<"No Cards yet"<<endl;
}

/*Controls CPUs' plays*/
void CPU_play(vector<Card> &v, Player_Id p)
{
	int initial_handsize=v.size();
	
	/*if CPU is first to play*/
	if(turn_num==0)
	{
		/*Find diamond 3 and discard if first turn*/
		for(int i=0;i<v.size();i++)
		{
			if((v[i].rank==0)&&(v[i].suit==0))
			{
				cout << player_turn_s[p] << " discarded "<< v[i].display()<< endl;
				discard1(i, p, v);	
				break;			
			}	
				
		}
	}

	/*CPU actions for other turns.*/
	else if(turn_num!=0)
	{
		int num_cards = v.size();

		sort(v, num_cards);//sort cards by ascending rank
	
		if(pile_owner==p) //if particular CPU player is pile owner, discard the smallest single card.
		{
			cout << player_turn_s[p]  << " discarded "<< v[0].display()<<endl;
			discard1(0,p,v);//discard smallest single card
		}
		if(pile_owner!=p) //if particular CPU player is not pile owner.
		{
			if(pile_type==Single) // discard single card if rank larger than pile. If rank same, discard if suit is higher.
			{
				for(int i=0;i<v.size();)
				{
					if(v[i].rank>pile[0].rank)
					{
						cout << player_turn_s[p]  << " discarded "<< v[i].display()<<endl;
						discard1(i,p,v);						
						break;
					}
						
					else if(v[i].rank==pile[0].rank)
					{
						if(v[i].suit>pile[0].suit)
						{						
							cout << player_turn_s[p]  << " discarded "<< v[i].display()<<endl;
							discard1(i,p,v);
							break;
						}
						
						else i++;
					}
					else i++;
				}
				
				if(v.size()==initial_handsize) //CPU skips if none are discarded
				{
					if(p==CPU1)
					{
						cout << player_turn_s[p] << " skipped"<<endl;
						player_turn=CPU2;
						
					}
					else if(p==CPU2)
					{
						cout << player_turn_s[p] << " skipped"<<endl;
						player_turn=CPU3;
						
					}
					else
					{
						cout<<player_turn_s[p]<<" skipped"<<endl; //show which turn
						player_turn=Player;
			
					}
				
					turn_num+=1; //increment turn
				}
		
			}
			if(pile_type==Pair)
			{
				for(int i=1;i<v.size();) //find duplicates by comparing adjacents, if rank is higher than pile, discard
				{
					if((v[i].rank==v[i-1].rank) && (v[i].rank>pile[0].rank))
					{		
						cout << player_turn_s[p]  << " discarded "<< v[i].display()<< " & "<< v[i-1].display()<<endl;
						discard2(i,i-1, p, v);
						break;
					}
					else if((v[i].rank==v[i-1].rank) && (v[i].rank==pile[0].rank))
					{
						if((max(v[i].suit,v[i-1].suit))> (max(pile[0].suit,pile[1].suit)))
						{
							cout << player_turn_s[p] << " discarded "<< v[i].display()<< " & "<< v[i-1].display()<<endl;
							discard2(i,i-1, p, v);
							break;
						}	
							
						else i++;
					}
					else i++;
				}
				
				if(v.size()==initial_handsize) //CPU skips if none are discarded
				{
					if(p==CPU1)
					{
						cout << player_turn_s[p] << " skipped"<<endl;
						player_turn=CPU2;
						
					}
					else if(p==CPU2)
					{
						cout << player_turn_s[p] << " skipped"<<endl;
						player_turn=CPU3;
						
					}
					else
					{
						cout<< player_turn_s[p]<< " skipped"<<endl; //show which turn
						player_turn=Player;
			
					}
				
					turn_num+=1; //increment turn

		
				}		
			}
		}
	}
		
	
}

void sort(vector<Card> &v,int n) 
{
	int i,j,low;
	
	for (i=0;i<n-1;i++) {
		low = i;
		for (j = i+1;j<n;j++)
			if (v[j].rank < v[low].rank)
				low =j;
		if (i!=low)
			swap(&v[i],&v[low]);
	}
}

void swap(Card *p1, Card *p2) {
	Card temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void pause(int sec)
{
	for (int j = sec; j > 0; j--) 
	{
			cout  << ".";
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}


