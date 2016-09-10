


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
	int value = 0;
	for (int i = 0; i < numbOfCards; i++) {
		cout << Cards[i].rank << " of " << Cards[i].suit << " , ";
		value += Cards[i].value;
	}
	cout << '\n';
	cout << "You Have: " << value << endl;


}

void Player::NewHand() {
	numbOfCards = 0;
//	Cards[]
}
