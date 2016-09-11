// Ethan Makela
// BlackJack Simulation/Game
//?


#include <time.h>

#include "stdafx.h"
#include "Card.h"
#include "Player.h"
#include "Table.h"


int main()
{
	//Create the table
	//Dealer* Jim = new Dealer;
	Table* table = new Table;

	
	//Set up the Deck
	table->CreateDeck();
	//Add players to the table
	table->AddPlayers();
	//Shuffle
	table->KnuthShuffle();
	
	//Deal
	table->PlayHand();

	table->PrintDeck();
	table->PrintBurnPile();
	
	delete table;

	return 0;

}

