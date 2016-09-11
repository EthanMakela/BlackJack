#pragma once
#include <string>
#include <iostream>
#include "Card.h"
#include <vector>
using namespace std;


class Player {
public:
	Card* firstCard;
	Card* secondCard;
	Card Cards[20];
	int numbOfCards;
	int total;
	int bankRoll;
	int currentBet;
	int moneyWithdrawn;
	bool isDoubling;
	bool hasAce;
	bool isStanding;
	string name;
	Player();
	~Player();
	void PrintCards();
	void NewHand();
	
	
};
