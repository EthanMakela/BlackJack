#pragma once


#include "Dealer.h"
#include "Card.h"
#include "Player.h"


using namespace std;

 
class Table {
public:
	
	int numbOfPlayers;
	int numbOfDecks;
	int deckSize;
	int tableStakes;
	int handNumber;
	

	vector<Card> Deck;
	vector<Player*> PlayerList; 
	
	Table();
	~Table();
	void PlayHand(Dealer& Jim);
	//void SimluateHands(int numbOfHands);
	
	//Shuffling
	void KnuthShuffle(void);
	void Swap(Card& a, Card& b);
	bool TimeToShuffle(Dealer& Jim);
	//void Shuffle();
	int Random();
	//Setup
	void AddPlayers();
	void AddNewPlayers();
	void AddMoney();
	void RemovePlayer(Dealer& Jim);
	void CreateDeck();
	
	
	//Tests
	void PrintDeck(Dealer& Jim);
	void PrintBurnPile(Dealer& Jim);


private:
	//Dealer* Jim;
};


