// Ethan Makela
// BlackJack Simulation/Game


#include <time.h>

#include "stdafx.h"
#include "Card.h"
#include "Player.h"
#include "Table.h"


int main()
{
	//Create the table
	Table table;
	
	//Set up the Deck
	table.CreateDeck();
	//Add players to the table
	table.AddPlayers();
	//Shuffle
	//table.Shuffle();
	table.KnuthShuffle();
	//Deal
	table.PlayHand();

	table.PrintDeck();
	table.PrintBurnPile();

	return 0;

}

