#ifndef func_h
#define func_h

#include <vector>
#include <string>
#include <stdlib.h>
#include "player.h"
#include "deck.h"
#include "card.h"

enum Turn { first_round, started };
enum Pile { Single, Pair, NoCards };
extern const std::string pile_type_s[3];
extern const std::string pile_owner_s[5];
extern const std::string player_turn_s[5];

/*Global variable*/
extern int turn_num; // 0 on first round
extern Player_Id pile_owner;//NIL on first round
extern Pile pile_type;//NoCards on first round
extern Player_Id player_turn;//Variable to indicate whose turn
extern Card pile[2]; //array to store last discarded card

/*Function proto*/
int menu_lvl1(int i, std::vector<Card> &v);
int user_inputs(int x, std::vector<Card> &v);
int singlecard_checker(int single_card, std::vector<Card> &v, Player_Id p);
int paircard_checker(int pair1, int pair2, std::vector<Card> &v, Player_Id p);
int int_checker(int menu, std::vector<Card> &v); // 1 indicates function is called from menu lvl1. 2 from level 2 menu
void discard1(int discard_card, Player_Id p, std::vector<Card> &v);
void discard2(int discard_card1, int discard_card2, Player_Id p, std::vector<Card> &v);
void show_game_status();
void CPU_play(std::vector<Card> &v, Player_Id);
void sort(std::vector<Card> &v, int n);
void swap(Card *p1, Card *p2);
void pause(int sec);

#endif
