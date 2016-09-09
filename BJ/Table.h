#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "Card.h"
#include "Player.h"

using namespace std;

class Table {
public:
	int ithCard;
	int numbOfPlayers;
	int numbOfDecks;
	int deckSize;
	int minBet;
	int tableStakes;
	int handNumber;

	Card dealerFirst;
	Card dealerSecond;


	vector<Card> Deck;
	vector<Player> PlayerList;

	Table();
	~Table();
	void PlayHand();
	void Deal();
	void TakeBets();
	void PrintHand();
	void SimluateHands(int numbOfHands);
	
	//Shuffling
	void KnuthShuffle(void);
	void Swap(Card& a, Card& b);
	bool TimeToShuffle();
	//void Shuffle();
	int Random();
	//Setup
	void AddPlayers();
	void AddNewPlayers();
	void CreateDeck();
	//Tests
	void PrintDeck();
	void PrintBurnPile();



};


