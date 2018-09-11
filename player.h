#ifndef player_h
#define player_h

#include <iostream>
#include <string>
#include <stdlib.h>


class Player_profile
{
    private:
		std::string name="";
		int score;
    
    	
	public:
	    void set_name(int x);
		std::string get_name();
		int get_score();
		void set_score(int n);
};


#endif
