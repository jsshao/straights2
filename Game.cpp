#include <iostream>
#include <vector>
#include "Game.h"
#include "Card.h"
#include "Player.h"
#include "HumanStrategy.h"
#include "ComputerStrategy.h"
#include "RageQuit.h"
using namespace std;

// Constructor- shuffles deck, intialize players as human/computer, and deal out cards
Game::Game(bool isComputer[4]) {
    deck_.shuffle();
    
    for (size_t i = 0; i < 4; i++) {
        if (isComputer[i] == false) {
            players_.push_back(new Player(new HumanStrategy));
        } else if (isComputer[i] == true) {
            players_.push_back(new Player(new ComputerStrategy)); 
        }

        for (size_t j = 0; j < 13; j++) {
            players_[i]->addCard(deck_.deal());
        }
    }
}

// Dynamically deallocate players
Game::~Game() {
    for (size_t i = 0; i < players_.size(); i++) {
        delete players_[i];
    }
}

// Start the game until someone has won
void Game::start() {
    while (!hasWon()) {
        newRound();
        table_.clear();
    }
	vector<int> winners = winner(); 
    for (size_t i = 0; i < winners.size(); i++) {
		cout << "Player " << winners[i] << " wins!" << endl;
	}
}

// Play a new round of Straights
void Game::newRound() {
    // Clear all discards
    for (size_t i = 0; i < players_.size(); i++) {
        players_[i]->clearDiscards();
    }

    int starter = startingPlayer();

    cout << "A new round begins. It's player " << starter << "'s turn to play." << endl; 

    // Play a card or discard
    for (size_t i = 0; i < 52; i++) {
        try {
            Card played = players_[(starter + i - 1) % players_.size()]->play(table_, *this);
            table_.push_back(played);
            cout << "Player " << (starter + i - 1) % players_.size() + 1 << " plays " << played << "." << endl;
        } catch (const Card& card) {
            cout << "Player " << (starter + i - 1) % players_.size() + 1 << " discards " << card << "." << endl;
        } catch (const RageQuit& rq) {
            cout << "Player " << (starter + i - 1) % players_.size() + 1 << " ragequits. A computer will now take over." << endl;
            i--;
        }
    } 

    // At end of round, show each player's discards and score
    for (size_t i = 0; i < players_.size(); i++) {
        cout << "Player " << i+1 << "'s discards: ";
        players_[i]->printDiscards();
       

        int totScore = players_[i]->getTotalScore();
        int roundScore = players_[i]->getRoundScore();
        cout << "Player " << i+1 << "'s score: " << totScore  << " + " << roundScore << " = " << totScore + roundScore << endl;
        players_[i]->updateScore();
    }

    // reshuffle and deal
    deck_.shuffle();
    for (size_t i = 0; i < players_.size(); i++) {
        for (size_t j = 0; j < 13; j++) {
            players_[i]->addCard(deck_.deal());
        }
    }
}

// Print out the entire deck
void Game::printDeck() const {
    cout << deck_ << endl;
}

// RageQuit
void rageQuit(const int player) {
	players_[player-1].rageQuit();
}

// Find the starting player with seven of spades
int Game::startingPlayer() const {
    for (size_t i = 0; i < players_.size(); i++) {
        if (players_[i]->hasCard(Card(SPADE, SEVEN))) {
            return i+1;
        }
    }
    return 1;
}

// Determine whether game is over (score higher than 80)
bool Game::hasWon() const {
    for (size_t i = 0; i < players_.size(); i++) {
        if (players_[i]->getTotalScore() >= 80) {
            return true;
        }
    }
    
    return false;
}

// Determine winning player (lowest points)
vector<int> Game::winner() const {
    vector<int> winners;
	int minScore = 80;

    for (size_t i = 0; i < players_.size(); i++) {
        if (players_[i]->getTotalScore() < minScore) {
            minScore = players_[i]->getTotalScore();
        }
    }

	for (size_t i = 0; i < players_.size(); i++) {
		if (players_[i]->getTotalScore() == minScore) {
			winners.push_back(i+1);
		}
	}

    return winners;
}
