#pragma once
#include <string>
using namespace std;


class Card {
public:
	string rank;
	string suit;
	~Card();
	Card();
	Card(string r, string s);
};