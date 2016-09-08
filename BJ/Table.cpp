
#include <time.h>

#include "stdafx.h"
#include "Table.h"


Table::Table() {
	numbOfPlayers = 0;
	numbOfDecks = 0;
	deckSize = numbOfDecks * 52;
	minBet = 5;
	tableStakes = 100;
	vector<Player> PlayerList;
	vector<Card> Deck;
	handNumber = 0;
	ithCard = 0;
	cout << "What is the minimum bet on the table\n";
	cin >> minBet;
	srand(0);
	
}

void Table::PlayHand() {
	handNumber++;
	//system("clear");
	cout << "Place Your Bets\n";
	for (unsigned i = 0; i < PlayerList.size(); i++) {
		cout << PlayerList[i].name << " bets ";
		cin >> PlayerList[i].currentBet;
	}
	cout << "All bets are in\n";
	//Deal PLAYERS their FIRSTCARD
	for (int i = 0; i < PlayerList.size(); i++) {
		PlayerList[i].firstCard = Deck[ithCard];
		ithCard++;
	}
	//Deal the DEALLER their FIRSTCARD
	dealerFirst = Deck[ithCard];
	ithCard++;
	//Deal the PLAYERS their SECONDCARD
	for (int i = 0; i < PlayerList.size(); i++) {
		PlayerList[i].secondCard = Deck[ithCard];
		ithCard++;
	}
	//Deal the Dealler their SECONDCARD
	dealerSecond = Deck[ithCard];
	ithCard++;

	for (int i = 0; i < PlayerList.size(); i++) {
		cout << PlayerList[i].name << ": ";
		cout << PlayerList[i].firstCard.rank << " of ";
		cout << PlayerList[i].firstCard.suit << " , ";
		cout << PlayerList[i].secondCard.rank << " of ";
		cout << PlayerList[i].secondCard.suit << endl;
	}
	cout << "Dealer: ";
	cout << dealerFirst.rank << " of ";
	cout << dealerFirst.suit << " , ";
	cout << dealerSecond.rank << " of ";
	cout << dealerSecond.suit << endl;

}

bool Table::TimeToShuffle() {
	int size = Deck.size();
	int burnspot = size * .7;
	if (size - ithCard < burnspot) return true;
	return false;
}

void Table::AddPlayers() {
	cout << "Enter how many people you would like to play with you\n";
	cin >> numbOfPlayers;

	for (int i = 0; i < numbOfPlayers; i++) {
		Player newPlayer;
		cout << "Enter the name of the player entering\n";
		cin >> newPlayer.name;
		cout << "Enter " << newPlayer.name << "'s bankroll'\n";
		cin >> newPlayer.bankRoll;
		PlayerList.push_back(newPlayer);
	}
}

void Table::CreateDeck() {

	string cardNames[13] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
	string cardSuit[4] = { "Spades", "Hearts", "Diamonds", "Clubs" };
	cout << "How many decks?\n";
	cin >> numbOfDecks;
	for (int z = 0; z < numbOfDecks; z++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				Deck.push_back(Card(cardNames[j], cardSuit[i]));
			}
		}
	}


}

void Table::PrintDeck() {
	cout << "Printing Deck:\n";
	for (int i = ithCard; i < Deck.size(); i++) {
		cout << ' ' << Deck[i].rank << " of " << Deck[i].suit;
	} cout << '\n';

	cout << "DeckSize: " << Deck.size() - ithCard << "\n\n";
}

void Table::PrintBurnPile() {
	cout << "Printing BUrn Pile\n";
	for (int i = 0; i < ithCard; i++) {
		cout << ' ' << Deck[i].rank << " of " << Deck[i].suit;
	} cout << '\n';

	cout << "PileSize: " << ithCard << "\n\n";
}


/*void Table::Shuffle(){
vector< Card > firstHalf;
vector< Card > secondHalf;
int mid = Deck.size() / 2;
for(int shuffles = 0; shuffles < 10; shuffles++){
for(int i = 0; i < Deck.size(); i++){
if( i < mid) firstHalf.push_back(Deck[i]);
else secondHalf.push_back(Deck[i]);
}
Deck.erase(Deck.begin(), Deck.end());
for(int i = firstHalf.size()-1; i >= 0; i--){
Deck.push_back(firstHalf[i]);
Deck.push_back(secondHalf[i]);
}
firstHalf.erase(firstHalf.begin(), firstHalf.end());
secondHalf.erase(secondHalf.begin(), secondHalf.end());
}
}
*/


void Table::KnuthShuffle(void) {
	int rand;
	for (int i = Deck.size() - 1; i >= 0; i--) {
		rand = Random();
		Swap(Deck[i], Deck[rand]);
	}
}

void Table::Swap(Card& a, Card& b) {
	Card c = a;
	a = b;
	b = c;
}

int Table::Random() {
	int r = rand() % Deck.size(); // Randomizing the number between 0-51.
	return r;
}

Table::~Table()
{
}
