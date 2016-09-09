#pragma once
#include <string>
#include "Card.h"
using namespace std;


class Player {
public:
	Card firstCard;
	Card secondCard;
	int total;
	int bankRoll;
	int currentBet;
	string name;
	Player();
	~Player();
	
};
