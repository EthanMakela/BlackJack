
#include "stdafx.h"
#include "Dealer.h"

Dealer::Dealer()
{
	numbOfDealerCards = 0;
	ithCard = 0;
	cout << "What is the minimum bet on the table\n";
	cin >> minBet;
	hasAce = false;
	dealersCards = new Card[14];
}

Dealer::~Dealer()
{
	delete [] dealersCards;
	
}


void Dealer::TakeBets(vector<Player*>& PlayerList, Card** & Deck) {
	cout << "Place Your Bets\n";
	vector<Player*>::iterator it;
	Player* current;
	bool leavingPlayer = false;
	bool firstPlayerLeaving = false;

	for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
		if (firstPlayerLeaving == true) {
			it = PlayerList.begin();
			firstPlayerLeaving = false;
		}
		current = *it;
		cout << current->name << " bets ";
		cin >> current->currentBet;
		if (current->bankRoll < current->currentBet || current->currentBet < 0 || current->currentBet < minBet) {
			if (current->currentBet < 0) {
				cout << "Thats funny get off the table" << endl;
				//PrintPlayerStats
				leavingPlayer = true;
			}
			
			else if (current->currentBet < minBet) {
				cout << "Table mininum is " << minBet << endl;
			}
			else {
				cout << "You do not have enough money" << endl;
				cout << "You have $" << current->bankRoll << " left ";
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
					current->bankRoll += addedMoney;
					current->moneyWithdrawn += addedMoney;
					break;
				default:
					cout << "You can always sit out a hand by betting $0" << endl;
					break;
				}
			}
			if (leavingPlayer == false) {
				cout << "Place your bet" << endl;
				cin >> current->currentBet;
			}
		}

		if (current->bankRoll < current->currentBet && leavingPlayer == false) {
			cout << "Get off my table" << endl;
			leavingPlayer = true;
		}
		current->bankRoll -= current->currentBet;
		if (leavingPlayer == true) {
			if (PlayerList.size() == 1)
				//PrintFullStats
				exit(1);

			else {
				if (it == PlayerList.begin()) {
					firstPlayerLeaving = true;
					PlayerSwap(*PlayerList[0], *PlayerList[1]);
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


void Dealer::DealFirstTwo(vector<Player*>& PlayerList, Card** & Deck) {
	//Deal PLAYERS their FIRSTCARD
	Player* current;
	vector<Player*>::iterator it;
	for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
		current = *it;
		if (current->currentBet != 0) {
			current->Cards[0] = *Deck[ithCard];
			current->numbOfCards++;
			ithCard++;
		}
		*it = current;
	}
	//Deal the DEALLER their FIRSTCARD
	dealersCards[0] = *Deck[ithCard];
	//dealerFirst = &dealersCards[0];
	numbOfDealerCards++;
	ithCard++;
	//Deal the PLAYERS their SECONDCARD
	for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
		current = *it;
		if (current->currentBet != 0) {
			current->Cards[1] = *Deck[ithCard];
			current->numbOfCards++;
			ithCard++;
		}
		*it = current;
	}
	//Deal the Dealler their SECONDCARD
	dealersCards[1] = *Deck[ithCard];
	//dealerSecond = &dealersCards[1];
	numbOfDealerCards++;
	ithCard++;
	PrintHand(PlayerList);
}

void Dealer::Deal(vector<Player*>& PlayerList, Card** & Deck) {
	Player* current;
	vector<Player*>::iterator it;
	int curValue = 0;
	int answer;


	for (it = PlayerList.begin(); it != PlayerList.end(); it++) {


		current = *it;
		
		current->NewHand();
		curValue = current->Cards[0].value + current->Cards[1].value;
		//current.total = curValue;
		cout << current->name << " your up  ===================		Total: " << curValue << endl;
		for (unsigned i = 0; i < 2; i++) {
			if (current->Cards[i].isAce == true) {
				current->hasAce = true;
			}
		}
		if (curValue == 21) {
			cout << "BLACKJACK" << endl;
			current->bankRoll += ((current->currentBet * 1.5) + current->currentBet);  //pays 3 to 2 for a blackjack
			current->wasPayed = true;
			continue;
		}
		while (current->isStanding == false && current->isDoubling == false) {
			if (current->Cards[current->numbOfCards-1].isAce) {
				current->hasAce = true;
			}
			
			if (curValue > 21) {
				cout << current->name << " BUST" << endl;
				current->hasBusted = true;
				break;
			}
			cout << current->name << " 1) Hit	    	2) Stand		3) Split		4) Double" << endl;
			cin >> answer;

			switch (answer) {
			case 1: //HIT
				current->Cards[current->numbOfCards] = *Deck[ithCard];
				curValue += Deck[ithCard]->value;
				current->total = curValue;
				ithCard++;
				current->numbOfCards++;
				current->PrintCards();
				break;
			case 2: //STAND
				current->isStanding = true;
				break;
			case 3:
				//TO come
			case 4: //DOUBLE DOWN
				curValue += Deck[ithCard]->value;
				current->Cards[current->numbOfCards] = *Deck[ithCard];
				current->total += curValue;
				ithCard++;
				current->numbOfCards++;
				current->PrintCards();
				if (current->bankRoll > 2 * current->currentBet) {
					current->isDoubling = true;
					current->bankRoll -= current->currentBet;  //take out the doubled bet from bankroll
					current->currentBet = current->currentBet * 2; //and double the bet

				}
				break;

			default:
				cout << "Invalid option.. Standing by default" << endl;
				current->isStanding = true;
				break;
			}


		}


		if (curValue > 21 && current->hasAce) {
			curValue -= 10;
			current->hasAce = false;

		}
		*it = current;
	}//End For
	DealerAI(PlayerList, Deck);

}

void Dealer::DealerAI(vector<Player*>& PlayerList, Card** & Deck) {
	vector<Player*>::iterator it;
	Player* current;
	//total = dealerFirst->value + dealerSecond->value;
	NewHand();
	for (unsigned i = 0; i < 2; i++) {
		total += dealersCards[i].value;
		if (dealersCards[i].isAce == true) {
			hasAce = true;
		}
	}
	if (total == 21) {
		cout << "Dealer BLACKJACK" << endl;
		for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
			current = *it;
			if (current->wasPayed == false && current->total == 21) {
					cout << current->name << ": Push" << endl;
					current->bankRoll += current->currentBet;
			}
			*it = current;
		}

	}
	while (total < 17) {
		if (dealersCards[numbOfDealerCards-1].isAce == true) {
			hasAce = true;
		}
		cout << "Dealer HITS" << endl;
		dealersCards[numbOfDealerCards] = *Deck[ithCard];
		total += dealersCards[numbOfDealerCards].value;
		ithCard++;
		numbOfDealerCards++;
		if (total > 21 && hasAce == true) {
			total -= 10;
		}
		
	}
	PrintCards();
	if (total > 21) {
		cout << "Dealer Bust" << endl;
		for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
			current = *it;
			if (current->wasPayed == false && current->total <= 21) {
				cout << current->name << ": Wins " << current->currentBet << endl;
				current->bankRoll += current->currentBet * 2;
			}
			*it = current;
		}
	}
	else {
		for (it = PlayerList.begin(); it != PlayerList.end(); it++) {
			current = *it;
			if (current->total > total && current->hasBusted == false && current->wasPayed == false) {
				cout << current->name << ": Wins " << current->currentBet << endl;
				current->bankRoll += current->currentBet * 2;
			}
			*it = current;
		}
	}

	
}

void Dealer::NewHand() {
	total = 0;
	numbOfDealerCards = 2;
}

int Dealer::getIthCard() {
	return ithCard;
}

void Dealer::PrintHand(vector<Player*>& PlayerList) {
	for (int i = 0; i < PlayerList.size(); i++) {
		cout << PlayerList[i]->name << ": ";
		cout << PlayerList[i]->Cards[0].rank << " of ";
		cout << PlayerList[i]->Cards[0].suit << " , ";
		cout << PlayerList[i]->Cards[1].rank << " of ";
		cout << PlayerList[i]->Cards[1].suit << endl;
	}
	cout << "Dealer: ";
	//cout << dealerFirst.rank << " of ";
	//cout << dealerFirst.suit << " , ";
	cout << dealersCards[1].rank << " of ";
	cout << dealersCards[1].suit << endl;
}

/*		cout << PlayerList[i].name << ": ";
		cout << PlayerList[i].firstCard->rank << " of ";
		cout << PlayerList[i].firstCard->suit << " , ";
		cout << PlayerList[i].secondCard->rank << " of ";
		cout << PlayerList[i].secondCard->suit << endl;*/


void Dealer::PrintCards() {
	int value = 0;
	cout << "Dealers's Hand: ";
	for (int i = 0; i < numbOfDealerCards; i++) {
		cout << " " << dealersCards[i].rank << " of " << dealersCards[i].suit << " , ";

	}
	cout << '\n';
	cout << "Total: " << total << endl;
	

}
void Dealer::PlayerSwap(Player& a, Player& b) {
	Player c = a;
	a = b;
	b = c;
}
