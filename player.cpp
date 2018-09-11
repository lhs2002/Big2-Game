#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include "player.h"

using namespace std;

void Player_profile::set_name(int x)
{
	if (x == 0)
	{
		while (name.empty()) // while name is empty keep prompting
		{
			std::cout << "What is your name?" << std::endl;
			getline(cin, name);
		}
	}
	else if (x == 1)
		name = "CPU1";
	else if (x == 2)
		name = "CPU2";
	else
		name = "CPU3";
}

string Player_profile::get_name()
{
	return name;
}

int Player_profile::get_score()
{
	return score;
}

void Player_profile::set_score(int n)
{
	score = n;
}