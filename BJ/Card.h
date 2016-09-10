#pragma once
#include <string>
using namespace std;


class Card {
public:
	string rank;
	string suit;
	int value;
	bool isAce;
	~Card();
	Card();
	Card(string r, string s, int j);
};