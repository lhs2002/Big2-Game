#ifndef card_h
#define card_h


#include <string>



class Card 
{	
	public:
			
		int rank;
		int suit;
		
	   	Card();
	    	
		Card(int r, int s); 	
			
		std::string display();
	
		
};

#endif
