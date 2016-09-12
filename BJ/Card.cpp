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

Card& Card::operator=(const Card &rhs) {
	// Check for self-assignment!
	if (this == &rhs) {     // Same object?
		return *this;
	}
	this->rank = rhs.rank;
	this->suit = rhs.suit;
	this->value = rhs.value;
	this->isAce = rhs.isAce;

	return *this;
}