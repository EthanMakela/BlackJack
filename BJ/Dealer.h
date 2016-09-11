#pragma once

#include "Player.h"
#include "Table.h"
#include "Card.h"

using namespace std;

class Dealer
{
public:
	Card* dealerFirst;
	Card* dealerSecond;
	Card dealersCards[12];
	int numbOfDealerCards;
	int ithCard;
	int minBet;

	
	void DealFirstTwo(vector<Player>& PlayerList, vector<Card>& Deck);
	void Deal(vector<Player>& PlayerList, vector<Card>& Deck);
	void PlayerSwap(Player& a, Player& b);
	void TakeBets(vector<Player>& PlayerList, vector<Card>& Deck);
	int getIthCard();
	void PrintHand(vector<Player>& PlayerList);
	Dealer();
	~Dealer();
};

