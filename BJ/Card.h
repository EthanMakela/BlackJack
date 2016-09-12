#pragma once
#include <string>
using namespace std;


class Card {
public:
	string rank;
	string suit;
	int value;
	bool isAce;

	bool operator==(const Card& other) const;

	~Card();
	Card();
	Card* NewCard(string r, string s, int j);
	Card& Card::operator=(const Card &rhs);
};