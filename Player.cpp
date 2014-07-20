#include "Player.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Constructor that initializes the type of player (human/computer)
Player::Player() :
    round_score_(0),
    total_score_(0) 
{
}

// Dynamically deallocates the strategy
Player::~Player() {
}

// Clear all discards in player's hand
void Player::clearDiscards() {
    discards_.clear();
}

// Output the discarded cards at the end of each round
void Player::printDiscards() const {
    for (size_t j = 0; j < discards_.size(); j++) {
        cout << discards_[j] << (j == discards_.size() - 1 ? "" :" ");
    }
    cout << endl;
}

// Return discarded cards by the player
vector<Card> Player::getDiscards() {
	return discards_; 
}

// Accessor for the player's score for this round
int Player::getRoundScore() const {
    return round_score_;
}

// Accessor for the player's score cumulated in all the previous rounds
int Player::getTotalScore() const {
    return total_score_;
}

// Add a card to the player's hand
void Player::addCard(Card card) {
    hand_.push_back(card);
}

// Checks whether a player has a certain card
bool Player::hasCard(Card card) const {
    return find(hand_.begin(), hand_.end(), card) != hand_.end();
}

// Update the total score by adding the score from this round
void Player::updateScore() {
    total_score_ += round_score_;
    round_score_ = 0;
}

// Let the player perform his turn
Card Player::play(const Game& game) {
    if (!game.hasLegalMove()) 
        throw hand_[0];
    else {
        for (size_t i = 0; i < hand_.size(); i++) {
            if (game.isLegalMove(hand_[i]))
                return hand_[i];
        }
    }
}

vector<Card> Player::getHand() const {
    return hand_;
}

void Player::playCard(Card card) {
	hand_.erase(remove(hand_.begin(), hand_.end(), card));
}

void Player::discardCard(Card card) {
	playCard(card);
	discards_.push_back(card);
	round_score_ += card.getRank()+1;	
}
