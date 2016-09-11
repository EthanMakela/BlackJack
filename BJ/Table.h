#pragma once
#include "Card.h"
#include "Player.h"
#include "Dealer.h"

using namespace std;

 
class Table {
public:
	
	int numbOfPlayers;
	int numbOfDecks;
	int deckSize;
	int tableStakes;
	int handNumber;

	vector<Card> Deck;
	vector<Player> PlayerList; 
	
	Table();
	~Table();
	void PlayHand();
	//void SimluateHands(int numbOfHands);
	
	//Shuffling
	void KnuthShuffle(void);
	void Swap(Card& a, Card& b);
	bool TimeToShuffle();
	//void Shuffle();
	int Random();
	//Setup
	void AddPlayers();
	void AddNewPlayers();
	void AddMoney();
	void RemovePlayer();
	void CreateDeck();
	void PlayerSwap(Player& a, Player& b);
	
	//Tests
	void PrintDeck();
	void PrintBurnPile();


private:
	//Dealer* Jim;
};


