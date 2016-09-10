


#include "stdafx.h"
#include "Table.h"


Table::Table() {
	numbOfPlayers = 0;
	numbOfDecks = 0;
	deckSize = numbOfDecks * 52;
	tableStakes = 100;
	vector<Player> PlayerList;
	vector<Card> Deck;
	handNumber = 0;
	numbOfDealerCards = 0;
	ithCard = 0;
	cout << "What is the minimum bet on the table\n";
	cin >> minBet;
	
	srand((unsigned)time(0));

	
}

void Table::PlayHand() {
	handNumber++;
	int answer;
	system("cls");

	
	TakeBets();
	DealFirstTwo();
	Deal();
	
	if (TimeToShuffle()) {
		cout << "Time To Shuffle" << endl;
		KnuthShuffle();
		ithCard = 0;
	}
	cout << "Play Again? " << endl;
	cout << "1) Yes		2) No	 3)	Hit the ATM		4)Add New Player	5)Remove Player" << endl;
	cin >> answer;
	switch (answer) {
	case 1:
		PlayHand();
		break;
	case 2:
		//PrintTableStats
		return;
	case 3:
		AddMoney();
		PlayHand();
		break;
	case 4:
		AddNewPlayers();
		PlayHand();
		break;
	case 5:
		if (PlayerList.size() == 1) return;
		RemovePlayer();
		PlayHand();
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
		cout << PlayerList[i].name << endl;
	}
	string playerName;
	cin >> playerName;
	Player temp;
	for (vector<Player>::iterator it = PlayerList.begin(); it != PlayerList.end(); it++) {
		temp = *it;
		if (playerName == temp.name) {
			int amount;
			cout << "Enter the amount of money you would like to add" << endl;
			cin >> amount;
			temp.bankRoll += amount;
			temp.moneyWithdrawn += amount;
			*it = temp;
			cout << temp.name << "'s new bankroll: " << temp.bankRoll << endl;
		}
	}
	cout << "There is no player by that name at this table... Try again next hand" << endl;
}


void Table::RemovePlayer() {
	cout << "Enter the name of the player that would like to leave" << endl;
	cout << "List of current players:" << endl;
	for (int i = 0; i < PlayerList.size(); i++) {
		cout << PlayerList[i].name << endl;
	}
	string leavingPlayer;
	cin >> leavingPlayer;
	Player temp;
	for (vector<Player>::iterator it = PlayerList.begin(); it != PlayerList.end(); it++) {
		temp = *it;
		if (leavingPlayer == temp.name) {

			if (PlayerList.size() == 1){
				//PrintFullStats
				exit(1);
			}
			else {
				if (it == PlayerList.begin()) {
					PlayerSwap(PlayerList[0], PlayerList[1]);
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
			Player newPlayer;
			cout << "Enter the name of the player entering\n";
			cin >> newPlayer.name;
			cout << "Enter " << newPlayer.name << "'s bankroll'\n";
			cin >> newPlayer.bankRoll;
			PlayerList.push_back(newPlayer);
		}
	}

}

void Table::TakeBets() {
	cout << "Place Your Bets\n";
	vector<Player>::iterator it; 
	Player current;
	bool leavingPlayer = false;
	bool firstPlayerLeaving = false;

	for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
		if (firstPlayerLeaving == true) {
			it = PlayerList.begin();
			firstPlayerLeaving = false;
		}
		current = *it;
		cout << current.name << " bets ";
		cin >> current.currentBet;
		if (current.bankRoll < current.currentBet || current.currentBet < 0 || current.currentBet < minBet) {
			if (current.currentBet < 0) {  
				cout << "Thats funny get off the table" << endl;
				//PrintPlayerStats
				leavingPlayer = true;
			}
			else if (current.currentBet < minBet) {
				cout << "Table mininum is " << minBet << endl;
			}
			else {
				cout << "You do not have enough money" << endl;
				cout << "You have $" << current.bankRoll << " left ";

				cout << "Would you still like to play?" << endl;
				cout << "1) Leave Table		2)Add Money		3)Keep Playing" << endl;

				int answer;
				cin >> answer;
				switch (answer) {
				case 1:
					//PrintPlayerStats();
					leavingPlayer = true;

					break;
				case 2:
					cout << "How much money would you like to add to your bankroll" << endl;
					int addedMoney;
					cin >> addedMoney;
					current.bankRoll += addedMoney;
					current.moneyWithdrawn += addedMoney;
					break;
				default:
					cout << "You can always sit out a hand by betting $0" << endl;
					break;
				}
			}
			if (leavingPlayer == false) {
				cout << "Place your bet" << endl;
				cin >> current.currentBet;
			}
		}

		if (current.bankRoll < current.currentBet && leavingPlayer == false) {
			cout << "Get off my table" << endl;
			leavingPlayer = true;
		}
		current.bankRoll -= current.currentBet;
		if (leavingPlayer == true) {
			if (PlayerList.size() == 1)
				//PrintFullStats
				exit(1);

			else {
				if (it == PlayerList.begin()) {
					firstPlayerLeaving = true;					
					PlayerSwap(PlayerList[0], PlayerList[1]);
					PlayerList.erase(it + 1);	
					//Error when first person leaves game
				}
				else {
					it--;
					PlayerList.erase(it + 1);
				}
			}
		}
		else {
			*it = current;
		}
	}
	cout << "All bets are in\n";
}


void Table::DealFirstTwo() {
	//Deal PLAYERS their FIRSTCARD
	Player current;
	vector<Player>::iterator it;
	for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
		current = *it;
		if (current.currentBet != 0) {
			current.Cards[0] = Deck[ithCard];
			current.firstCard = current.Cards[0];
			current.numbOfCards++;
			ithCard++;
		}
		*it = current;
	}
	//Deal the DEALLER their FIRSTCARD
	dealersCards[0] = Deck[ithCard];
	dealerFirst = dealersCards[0];
	numbOfDealerCards++;
	ithCard++;
	//Deal the PLAYERS their SECONDCARD
	for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
		current = *it;
		if (current.currentBet != 0) {
			current.Cards[1] = Deck[ithCard];
			current.secondCard = current.Cards[1];
			current.numbOfCards++;
			ithCard++;
		}
		*it = current;
	}
	//Deal the Dealler their SECONDCARD
	dealersCards[1] = Deck[ithCard];
	dealerSecond = dealersCards[1];
	numbOfDealerCards++;
	ithCard++;
	PrintHand();
}

void Table::Deal() {
	Player current;
	vector<Player>::iterator it;
	int curValue = 0;
	int answer;
	bool stand = false;
	for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
		
		
		current = *it;
		curValue = current.firstCard.value + current.secondCard.value;
		if (curValue == 21) {
			cout << "BLACKJACK" << endl;
			current.bankRoll = current.currentBet * 1.5;
			continue;
		}
		while (curValue <= 21 && stand == false) {
			stand = false;
			current.numbOfCards++;
			cout << current.name << " 1) Hit	    	2) Stand		3) Split		4) Double" << endl;
			cin >> answer;
			
			switch (answer) {
			case 1:
				current.Cards[current.numbOfCards-1] = Deck[ithCard];
				curValue += Deck[ithCard].value;
				ithCard++;
				break;


			}
			cout << current.name << "'s Hand: ";
			current.PrintCards();
		}
		current.numbOfCards = 0;
		*it = current;
	}//End For
}

void Table::PrintHand() {
	for (int i = 0; i < PlayerList.size(); i++) {
		cout << PlayerList[i].name << ": ";
		cout << PlayerList[i].firstCard.rank << " of ";
		cout << PlayerList[i].firstCard.suit << " , ";
		cout << PlayerList[i].secondCard.rank << " of ";
		cout << PlayerList[i].secondCard.suit << endl;
	}
	cout << "Dealer: ";
	//cout << dealerFirst.rank << " of ";
	//cout << dealerFirst.suit << " , ";
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
	cout << "Enter how many people you would like to play with you (MAX 7)\n";
	cin >> numbOfPlayers;
	if (numbOfPlayers > 7) exit(2);
	for (int i = 0; i < numbOfPlayers; i++) {
		Player newPlayer;
		cout << "Enter the name of the player entering\n";
		cin >> newPlayer.name;
		cout << "Enter " << newPlayer.name << "'s bankroll'\n";
		int bankRoll;
		cin >> bankRoll;
		newPlayer.bankRoll = bankRoll;
		newPlayer.moneyWithdrawn = bankRoll;
		PlayerList.push_back(newPlayer);
	}
}

void Table::CreateDeck() { 

	string cardNames[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string cardSuit[4] = { "Spades", "Hearts", "Diamonds", "Clubs" };
	
	cout << "How many decks?\n";
	cin >> numbOfDecks;
	for (int z = 0; z < numbOfDecks; z++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				Deck.push_back(Card(cardNames[j], cardSuit[i], j));
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

void Table::PlayerSwap(Player& a, Player& b){
	Player c = a;
	a = b;
	b = c;
}




