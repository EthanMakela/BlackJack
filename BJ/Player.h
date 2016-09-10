#pragma once
#include <string>
#include "Card.h"
#include <vector>
using namespace std;


class Player {
public:
	Card firstCard;
	Card secondCard;
	vector<Card> extraCards;
	int total;
	int bankRoll;
	int currentBet;
	int moneyWithdrawn;
	string name;
	Player();
	~Player();
	
	
};
