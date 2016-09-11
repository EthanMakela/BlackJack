// Ethan Makela
// BlackJack Simulation/Game





#include "stdafx.h"


#include "Table.h"
#include "Dealer.h"




int main()
{
	//Create the table
	
	Table* table = new Table();
	Dealer* Jim = new Dealer();
	
	//Set up the Deck
	table->CreateDeck();
	//Add players to the table
	table->AddPlayers();
	//Shuffle
	table->KnuthShuffle();
	
	//Deal
	table->PlayHand(*Jim);

	table->PrintDeck(*Jim);
	table->PrintBurnPile(*Jim);
	//table->EndGame();
	
	delete table;
	delete Jim;

	return 0;

}

