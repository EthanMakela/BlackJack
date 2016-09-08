#include "stdafx.h"
#include "Card.h"


Card::Card() {
	rank = ' ';
	suit = ' ';
}

Card::Card(string r, string s)
{
	rank = r;
	suit = s;
}

Card::~Card()
{
}
