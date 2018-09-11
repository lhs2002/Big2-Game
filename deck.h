#ifndef deck_h
#define deck_h

#include <vector>
#include "card.h"
#include <ctime>


enum Player_Id {Player, CPU1, CPU2, CPU3, NIL};


class Deck
{
	
	private:
		std::vector<Card> deck_cards;

	public:	
		std::vector<Card> player_hand;
		std::vector<Card> CPU1_hand;
		std::vector<Card> CPU2_hand;
		std::vector<Card> CPU3_hand;	
		
		Deck();
		void display();
		void deal_hand();
		void display_player();
		void display_CPU1();
		void display_CPU2();
		void display_CPU3();
		Player_Id find_starting();
		int cardsnum(Player_Id p);
		Player_Id game_win();
		
};



#endif
