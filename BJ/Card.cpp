#include "stdafx.h"
#include "Card.h"


Card::Card() {
	rank = ' ';
	suit = ' ';
	value = 0;
	isAce = false;
}

Card* Card::NewCard(string r, string s, int j)
{
	Card* temp = new Card();
	temp->rank = r;
	temp->suit = s;
	switch (j) {
		case 0:
			temp->isAce = true;
			temp->value = 11;
			break;
		case 10: 
			temp->value = 10;
			break;
		case 11:
			temp->value = 10;
			break;
		case 12:
			temp->value = 10;
			break;
		default:
			temp->value = j + 1;
			break;
	}
	return temp;
}

bool Card::operator==(const Card& other) const
{
	return ((rank == other.rank) && (suit == other.suit));
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