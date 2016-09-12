


#include "stdafx.h"
#include "Table.h"


Table::Table() {
	numbOfPlayers = 1;
	numbOfDecks = 0;
	
	tableStakes = 100;
	Deck = new Card*[deckSize];
	handNumber = 0;
	srand((unsigned)time(0));
	cout << "How many decks?\n";
	cin >> numbOfDecks;
	deckSize = numbOfDecks * 52;
	cout << "Enter how many people you would like to play with you (MAX 7)\n";
	cin >> numbOfPlayers;
	
	
}

Table::~Table() {
	for (int i = 0; i < PlayerList.size(); i++) {
		delete PlayerList[i];
	}
	for (int i = 0; i < deckSize; i++){
		delete Deck[i];
	}
	
}




void Table::PlayHand(Dealer& Jim) {
	
	handNumber++;
	int answer;
	//system("cls");

	
	Jim.TakeBets(PlayerList, Deck);
	Jim.DealFirstTwo(PlayerList, Deck);
	Jim.Deal(PlayerList, Deck);
	
	if (TimeToShuffle(Jim)) {
		cout << "Time To Shuffle" << endl;
		KnuthShuffle();
		Jim.ithCard = 0;
	}
	cout << "Play Again? " << endl;
	cout << "1) Yes		2) No	 3)	Hit the ATM		4)Add New Player	5)Remove Player" << endl;
	cin >> answer;
	switch (answer) {
	case 1:
		PlayHand(Jim);
		break;
	case 2:
		//PrintTableStats
		return;
	case 3:
		AddMoney();
		PlayHand(Jim);
		break;
	case 4:
		AddNewPlayers();
		PlayHand(Jim);
		break;
	case 5:
		if (PlayerList.size() == 1) return;
		RemovePlayer(Jim);
		PlayHand(Jim);
		break;
	default:
		//PrintStats
		//PlayHand();
		break;
	}
	
	
}


void Table::AddMoney() {
	cout << "Enter the name of the player who would like to buy in" << endl;
	cout << "List of current players:" << endl;
	for (int i = 0; i < PlayerList.size(); i++) {
		cout << PlayerList[i]->name << endl;
	}
	string playerName;
	cin >> playerName;
	Player* temp;
	for (vector<Player*>::iterator it = PlayerList.begin(); it != PlayerList.end(); it++) {
		temp = *it;
		if (playerName == temp->name) {
			int amount;
			cout << "Enter the amount of money you would like to add" << endl;
			cin >> amount;
			temp->bankRoll += amount;
			temp->moneyWithdrawn += amount;
			*it = temp;
			cout << temp->name << "'s new bankroll: " << temp->bankRoll << endl;
		}
	}
	cout << "There is no player by that name at this table... Try again next hand" << endl;
}


void Table::RemovePlayer(Dealer& Jim) {
	cout << "Enter the name of the player that would like to leave" << endl;
	cout << "List of current players:" << endl;
	for (int i = 0; i < PlayerList.size(); i++) {
		cout << PlayerList[i]->name << endl;
	}
	string leavingPlayer;
	cin >> leavingPlayer;
	Player* temp;
	for (vector<Player*>::iterator it = PlayerList.begin(); it != PlayerList.end(); it++) {
		temp = *it;
		if (leavingPlayer == temp->name) {

			if (PlayerList.size() == 1){
				//PrintFullStats
				exit(1);
			}
			else {
				if (it == PlayerList.begin()) {
					Jim.PlayerSwap(*PlayerList[0], *PlayerList[1]);
					PlayerList.erase(it + 1);
					
				}
				else {
					it--;
					PlayerList.erase(it + 1);
				}
			}

		}
		return;
	}
	
	cout << "There is no player by that name at this table... Try again next hand" << endl;
}


void Table::AddNewPlayers() {
	cout << "Enter the number of new players (MAX 7 at the table)" << endl;
	cout << "There are " << PlayerList.size() << " people at the table now" << endl;
	int NumberOfNewPlayers;
	cin  >> NumberOfNewPlayers;
	if (NumberOfNewPlayers + PlayerList.size() > 7) {
		cout << "Too many people... Try again after the next hand" << endl;
		return;
	}
	else{
		for (int i = 0; i < NumberOfNewPlayers; i++) {
			Player* newPlayer = new Player();
			cout << "Enter the name of the player entering\n";
			cin >> newPlayer->name;
			cout << "Enter " << newPlayer->name << "'s bankroll'\n";
			cin >> newPlayer->bankRoll;
			PlayerList.push_back(newPlayer);
		}
	}

}

bool Table::TimeToShuffle(Dealer& Jim) {
	int size = deckSize;
	int burnspot = size * .7;
	if (size - Jim.ithCard < burnspot) return true;
	return false;
}

void Table::AddPlayers() {
	
	//Player* newPlayers = new Player[numbOfPlayers];
	for (int i = 0; i < numbOfPlayers; i++) {
		Player* newPlayer = new Player();
		cout << "Enter the name of the player entering\n";
		cin >> newPlayer->name;
		cout << "Enter " << newPlayer->name << "'s bankroll'\n";
		cin >> newPlayer->bankRoll;
		newPlayer->moneyWithdrawn = newPlayer->bankRoll;
		PlayerList.push_back(newPlayer);
		
	}
}

void Table::CreateDeck() { 

	string cardNames[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string cardSuit[4] = { "Spades", "Hearts", "Diamonds", "Clubs" };
	
	
	int count = 0;
	for (int z = 0; z < numbOfDecks; z++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				Deck[count] = Deck[count]->NewCard(cardNames[j], cardSuit[i], j);
				count++;
			}
		}
	}


}

void Table::PrintDeck(Dealer& Jim) {
	cout << "Printing Deck:\n";
	for (unsigned i = Jim.ithCard; i < deckSize; i++) {
		cout << ' ' << Deck[i]->rank << " of " << Deck[i]->suit;
	} cout << '\n';

	cout << "DeckSize: " << deckSize - Jim.ithCard << "\n\n";
}

void Table::PrintBurnPile(Dealer& Jim) {
	cout << "Printing BUrn Pile\n";
	for (int i = 0; i < Jim.ithCard; i++) {
		cout << ' ' << Deck[i]->rank << " of " << Deck[i]->suit;
	} cout << '\n';

	cout << "PileSize: " << Jim.ithCard << "\n\n";
}

//Old Shuffling method...More like real shuffling less efficient
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
	for (int i = deckSize - 1; i >= 0; i--) {
		rand = Random();
		Swap(*Deck[i], *Deck[rand]);
	}
}

void Table::Swap(Card& a, Card& b) {
	Card c = a;
	a = b;
	b = c;
}

int Table::Random() {
	int r = rand() % deckSize; // Randomizing the number between 0-51.
	return r;
}






