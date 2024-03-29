#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <sstream>
#include "Card.h"
#include "Game.h"


class Player {
    public:
        // Constructor
        Player();
        
        // Destructor
        ~Player();

        // Plays a card
        Card play(const Game& game);

        // Print discarded cards by the player
        void printDiscards(std::stringstream &) const;

		// Return discarded cards by the player
		std::vector<Card> getDiscards();
    
        // Clear the discards from the player after each round
        void clearDiscards();

        // Accessor for Player's round score
        int getRoundScore() const;

        // Accessor for Player's total score
        int getTotalScore() const;

        // Add a card to the players hand
        void addCard(Card card);

        // Determine whether a player has a certain card in the hand
        bool hasCard(Card card) const;

		// Play the card (remove from hand)
		void playCard(Card card);

		// Discard the card (remove from hand, add to discard pile, and add point)
		void discardCard(Card card);

        // Update total score by adding the round score
        void updateScore();

        std::vector<Card> getHand() const;
    
    private:
        // Scores
        int round_score_;
        int total_score_;
        
        // Keep track of the player's hand and cards they discarded
        std::vector<Card> discards_;
        std::vector<Card> hand_;

        // Disallow equality operator, assignment operator, and copy constructor
        bool operator==(const Player& player);
        void operator=(const Player& player);
        Player(const Player& player);
};

#endif
