#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include "card.h"

using namespace std;

Card::Card() {}

Card::Card(int r, int s) 
{
	rank = r; suit = s; 
}
		
string Card:: display()
{
	static const string aRanks[] = {" 3", " 4"," 5", " 6", " 7", " 8", " 9", "10", " J", " Q", " K", " A"," 2"};
	static const string aSuits[] = {"diamonds", "clubs", "hearts", "spades"};
		
	return aRanks[rank] + " of " + aSuits[suit];
}
