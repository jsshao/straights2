#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include "Model.h"
#include "Game.h"
#include "Card.h"
#include "Player.h"
using namespace std;

bool Game::isLegalMove(Card card) const {
    if (card.getRank() == SEVEN and card.getSuit() == SPADE)
        return true;

    if (players_[cur_player_ - 1 ]->hasCard(Card(SPADE, SEVEN)))
        return false;

    return high[(int)card.getSuit()] == card.getRank() 
        or low[(int)card.getSuit()] == card.getRank();
}

// Constructor- shuffles deck, intialize players as human/computer, and deal out cards
Game::Game(bool isComputer[4], Model *model) : model_(model) {
    deck_.shuffle();
    
    for (size_t i = 0; i < 4; i++) {
        is_computer[i] = isComputer[i]; players_.push_back(new Player()); 

        for (size_t j = 0; j < 13; j++) {
            players_[i]->addCard(deck_.deal());
        }
    }
    cur_player_ = startingPlayer();
	newRound();
}


// Dynamically deallocate players
Game::~Game() {
    for (size_t i = 0; i < players_.size(); i++) {
        delete players_[i];
    }
}

void Game::start() {
    while (!hasWon()) {
        newRound();
    }
	vector<int> winners = winner(); 
    for (size_t i = 0; i < winners.size(); i++) {
		cout << "Player " << winners[i] << " wins!" << endl;
	}
}

bool Game::hasLegalMove() const {
    vector<Card> hand = getHand(cur_player_);
    for (size_t i = 0; i < hand.size(); i++) {
        if (isLegalMove(hand[i])) 
            return true;
    }
    return false;
}

void Game::play(Card c) {
    // Play a card or discard TODO: for now it always plays the card (need to check and add discard)
    if (isLegalMove(c)) {
        table_.push_back(c);
        int suit = (int)c.getSuit();
        if (c.getRank() == high[suit]) high[suit]++;
        if (c.getRank() == low[suit]) low[suit]--;
        cout << "Player " << cur_player_ << " plays " << c << "." << endl;
        players_[cur_player_-1]->playCard(c);
    } 
    else if (!hasLegalMove()) {
        players_[cur_player_-1]->discardCard(c);
        cout << "Player " << cur_player_ << " discards " << c << "." << endl;
    }
    else {
        cout << ">This is not a legal play." << endl;
        return;
    }

    turns_++;
    cur_player_ = cur_player_ % 4 + 1;
    playAI();
}

void Game::rageQuit() {
    is_computer[cur_player_ - 1] ^= 1;
    cout << "Player " << cur_player_ << " ragequits. A computer will now take over." << endl;
    playAI(); 
}

void Game::playAI() {
    while (is_computer[cur_player_-1] and turns_ < 52) { 
        try {
            Card played = players_[cur_player_ - 1]->play(*this);
            table_.push_back(played);
            players_[cur_player_ - 1]->playCard(played);
			int suit = (int)played.getSuit();
            if (played.getRank() == high[suit]) high[suit]++;
            if (played.getRank() == low[suit]) low[suit]--;
            cout << "Player " << cur_player_ << " plays " << played << "." << endl;
        } catch (const Card& card) {
            cout << "Player " << cur_player_ << " discards " << card << "." << endl;
    		players_[cur_player_ - 1]->discardCard(card);
	    } 
        turns_++;
        cur_player_ = cur_player_ % 4 + 1;
    }
    if (turns_ == 52) { 
        endRound();
    }
}

// Play a new round of Straights
void Game::newRound() {
    // Clear all discards
    for (size_t i = 0; i < players_.size(); i++) {
        players_[i]->clearDiscards();
    }

	// Clear the table
	table_.clear();
    for (int i = 0; i < 4; i++) {
        high[i] = SEVEN;
        low[i] = SEVEN;
    }

    turns_ = 0;
    int starter = startingPlayer();

	stringstream ss;
	ss << startingPlayer();
    model_->setMessage("A new round begins. It's player " + ss.str() + "'s turn to play.");
	
    cout << "A new round begins. It's player " << starter << "'s turn to play." << endl; 
    playAI();
}

void Game::endRound() {
    // At end of round, show each player's discards and score
    stringstream ss;
	
	for (size_t i = 0; i < players_.size(); i++) {
        ss << "Player " << i+1 << "'s discards: ";
        players_[i]->printDiscards(ss);
       
        int totScore = players_[i]->getTotalScore();
        int roundScore = players_[i]->getRoundScore();
        ss << "Player " << i+1 << "'s score: " << totScore  << " + " << roundScore << " = " << totScore + roundScore << endl;
        players_[i]->updateScore();
    }
	model_->setMessage(ss.str());

    // reshuffle and deal
    deck_.shuffle();
    for (size_t i = 0; i < players_.size(); i++) {
        for (size_t j = 0; j < 13; j++) {
            players_[i]->addCard(deck_.deal());
        }
    }
	if (!hasWon()) {
		newRound();
	} else {
		stringstream ss;
		vector<int> winners = winner(); 
    	for (size_t i = 0; i < winners.size(); i++) {
			ss << "Player " << winners[i] << " wins!" << endl;
		}
		model_->setMessage(ss.str());
		model_->endGame();
	}
}


// Print out the entire deck
void Game::printDeck() const {
    cout << deck_ << endl;
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

vector<int> Game::scores() const {
	vector<int> scores;
	for (size_t i = 0; i < players_.size(); i++) {
		scores.push_back(players_[i]->getTotalScore());
	}

	return scores;
}

vector<vector<Card> > Game::discards() const {
	vector<vector<Card> > Discards;
	for (size_t i = 0; i < players_.size(); i++) {
		Discards.push_back(players_[i]->getDiscards());
	}
	
	return Discards;
}

vector<Card> Game::getTable() const {
    return table_;
};

vector<Card> Game::getHand(int who) const {
    return players_[who-1]->getHand();
}

int Game::curPlayer() const {
    return cur_player_;
}
