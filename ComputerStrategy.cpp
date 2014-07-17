#include "ComputerStrategy.h"

using namespace std;

// Implementation of play from a computer
Card ComputerStrategy::play(const vector<Card>& table, const vector<Card>& hand, const Game& game) const {
    
    // Compute legal moves given the table and the current hand
    vector<Card> legal_moves = Strategy::computeLegalMoves(table, hand);
    
    // Play the first legal move if possible
    if (legal_moves.size()) {
        return legal_moves[0];
    }
    
    // Discard the first card in the hand if no legal moves
    throw hand[0];
}

