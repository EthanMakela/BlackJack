#include "stdafx.h"
#include "Card.h"


Card::Card() {
	rank = ' ';
	suit = ' ';
	value = 0;
	isAce = false;
}

Card::Card(string r, string s, int j)
{
	
	rank = r;
	suit = s;
	switch (j) {
		case 0:
			isAce = true;
			value = 11;
			break;
		case 10: 
			value = 10;
			break;
		case 11:
			value = 10;
			break;
		case 12:
			value = 10;
			break;
		default:
			value = j + 1;
			break;
	}
}

Card::~Card()
{
}
