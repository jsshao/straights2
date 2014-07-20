#include "Player.h"
#include "Card.h"
#include "ComputerStrategy.h"
#include "RageQuit.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Constructor that initializes the type of player (human/computer)
Player::Player(Strategy* strategy) :
    strategy_(strategy),
    round_score_(0),
    total_score_(0) 
{
}

// Dynamically deallocates the strategy
Player::~Player() {
    delete strategy_;
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
Card Player::play(const vector<Card>& table, const Game& game) {
    // Play a card and destroy it from hand
    try {
        Card card = strategy_->play(table, hand_, game);
        for (size_t i = 0; i < hand_.size(); i++) {
            if (hand_[i] == card) {
                hand_.erase(hand_.begin() + i);
            }
        }
        return card;
    } 
    // Ragequits by throwing RageQuit exception
    catch (const RageQuit& rq) {
        ragequit();
        throw rq;
    }
    // Discards a card, add it to discards, update score and remove from hand
    catch (const Card &card) {
        round_score_+= card.getRank()+1;
        discards_.push_back(card);
        for (size_t i = 0; i < hand_.size(); i++) {
            if (hand_[i] == card) {
                hand_.erase(hand_.begin() + i);
            }
        }
        throw card;
    }
}

// Ragequit by deleting human strategy and reimplementing strategy as a computer player
void Player::ragequit() {
    delete strategy_;
    strategy_ = new ComputerStrategy;
}

vector<Card> Player::getHand() const {
    return hand_;
}
