// Ethan Makela
// BlackJack Simulation/Game





#include "stdafx.h"


#include "Table.h"





int main()
{
	//Create the table
	
	Table* table = new Table();
	
	
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
	//table->EndGame();
	
	delete table;

	return 0;

}

