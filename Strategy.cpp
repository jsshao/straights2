#include "Strategy.h"
#include <algorithm>
#include <vector>

using namespace std;

vector<Card> Strategy::computeLegalMoves(const vector<Card>& table, const vector<Card>& hand) {
    // Create legal moves
    vector<Card> legal_moves;

    for (size_t i = 0; i < hand.size(); i++) {
        Card card = hand[i];
        if (card.getRank() == SEVEN) {
            // If player has 7S, that's the only legal move
            if (card.getSuit() == SPADE) {
                legal_moves.clear();
                legal_moves.push_back(card);
                break;
            }

            // Any 7 is a legal move
            legal_moves.push_back(card);
        } else {
            // Check if adjacent cards are on the table (if so, it is legal)
            
            if (card.getRank() != ACE) {
                Card lower = Card(card.getSuit(), Rank(card.getRank() - 1));
                if (find(table.begin(), table.end(), lower) != table.end()) {
                    legal_moves.push_back(card);
                    continue;
                }    
            } 
            
            if (card.getRank() != KING) {
                Card higher = Card(card.getSuit(), Rank(card.getRank() + 1));
                if (find(table.begin(), table.end(), higher) != table.end()) {
                    legal_moves.push_back(card);
                }
            }
        }
    }
    return legal_moves;
}
