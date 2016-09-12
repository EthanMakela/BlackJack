#pragma once
#include <string>
using namespace std;


class Card {
public:
	string rank;
	string suit;
	int value;
	bool isAce;

	bool operator==(const Card& other) const
	{
		return ((rank == other.rank) && (suit == other.suit));
	}

	~Card();
	Card();
	Card(string r, string s, int j);
	Card& Card::operator=(const Card &rhs);
};