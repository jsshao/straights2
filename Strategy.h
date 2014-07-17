#ifndef STRAT_H
#define STRAT_H

#include "Card.h"
#include "Game.h"
#include <vector>

class Strategy {
    public:
        // Pure virtual function that simulates human/computer's turn
        virtual Card play(const std::vector<Card>& legal_moves, const std::vector<Card>& hand, const Game& game) const = 0; 
        
        // Helper function to compute the legal moves knowing the table and the hand
        static std::vector<Card> computeLegalMoves(const std::vector<Card>& table, const std::vector<Card>& hand);
    private:
};

#endif
