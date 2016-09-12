#pragma once

#include "Card.h"

using namespace std;


class Player {
public:
	Card* Cards;

	int numbOfCards;
	int total;
	int bankRoll;
	int currentBet;
	int moneyWithdrawn;

	bool isDoubling;
	bool hasAce;
	bool isStanding;
	bool wasPayed;
	bool hasBusted;

	string name;

	Player();
	~Player();
	void PrintCards();
	void NewHand();
	
	
};
