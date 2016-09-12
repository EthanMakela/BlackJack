#pragma once

#include "Player.h"
#include "Card.h"

using namespace std;

class Dealer
{
public:
	Card* dealersCards;
	int numbOfDealerCards;
	int ithCard;
	int minBet;
	int total;
	bool hasAce;

	
	void DealFirstTwo(vector<Player*>& PlayerList, Card** & Deck);
	void Deal(vector<Player*>& PlayerList, Card** & Deck);
	void PlayerSwap(Player& a, Player& b);
	void TakeBets(vector<Player*>& PlayerList, Card** & Deck);
	int getIthCard();
	void PrintHand(vector<Player*>& PlayerList);
	void PrintCards();
	void DealerAI(vector<Player*>& PlayerList, Card** & Deck);
	void NewHand();

	Dealer();
	~Dealer();
};

