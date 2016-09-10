


#include "stdafx.h"
#include "Player.h"


Player::Player() {
	total = 0;
	bankRoll = 0;
	currentBet = 0;
	name = "JohnDoe";
	moneyWithdrawn = 0;
	numbOfCards = 0;
};

Player::~Player()
{
}

void Player::PrintCards() {
	for (int i = 0; i < numbOfCards; i++) {
		cout << Cards[i].rank << " of " << Cards[i].suit << " , ";
	}
	cout << '\n';
}

