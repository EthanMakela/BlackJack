


#include "stdafx.h"
#include "Player.h"


Player::Player() {
	total = 0;
	bankRoll = 0;
	currentBet = 0;
	name = "JohnDoe";
	moneyWithdrawn = 0;
	numbOfCards = 0;
	isDoubling = false;
	hasAce = false;
	isStanding = false;
};

Player::~Player()
{
}

void Player::PrintCards() {
	int value = 0;
	cout << name << "'s Hand: ";
	for (int i = 0; i < numbOfCards; i++) {
		cout << " " << Cards[i].rank << " of " << Cards[i].suit << " , ";
		
	}
	cout << '\n';

	cout << "Total: " << total << endl;
	

}

void Player::NewHand() {
	numbOfCards = 2;
	total = 0;
	isDoubling = false;
	hasAce = false;
	isStanding = false;
	wasPayed = false;
	hasBusted = false;
}
