#include <iostream>
#include <algorithm>
#include <vector>
#include "HumanStrategy.h"
#include "Command.h"
#include "RageQuit.h"
using namespace std;

// Compare function for cards (sort by suits first then rank)
bool compare(const Card& a, const Card& b) {
    return a.getSuit() * 100 + a.getRank() < b.getSuit() * 100 + b.getRank();
}

// Implmentation of human player's strategy (prompts user input)
Card HumanStrategy::play(const vector<Card>& table, const vector<Card>& hand, const Game& game) const {
    // Compute legal moves
    vector<Card> legal_moves = Strategy::computeLegalMoves(table, hand);
    
    // Sort table to output for user
    vector<Card> sorted = table;
    sort(sorted.begin(), sorted.end(), compare);

    // Output the table formatted by suits
    vector<vector<string> > by_suit;
	string suits[SUIT_COUNT] = {"Clubs: ", "Diamonds: ", "Hearts: ", "Spades: "};
    for (int i = 0; i < 4; i++) 
        by_suit.push_back(vector<string>());

    cout << "Cards on the table: " << endl;
    
    for (size_t i = 0; i < sorted.size(); i++) {
        by_suit[sorted[i].getSuit()].push_back(sorted[i].getRankName());
    }
    
    for (int i = 0; i < 4; i++) {
        cout << suits[i];
        bool first = true;
        for (size_t j = 0; j < by_suit[i].size(); j++) {
            if (!first) cout << " ";
            first = false;
            cout << by_suit[i][j];
        }
        cout << endl;
    }
    
    // Output contents of the Player's hand
    cout << "Your hand: ";
    for (size_t i = 0; i < hand.size(); i++) {
        cout << hand[i];
        if (i != hand.size()-1)
            cout << " ";
    }

    // Output what legal moves user can make
    cout << endl << "Legal plays: ";
    for (size_t i = 0; i < legal_moves.size(); i++) {
        cout << legal_moves[i];
        if (i != legal_moves.size()-1)
            cout << " ";
    }
    cout << endl;

    // Prompt for user input until a legal return card is played (or an exception is thrown)
    while (true) {
        cout << ">";
        Command command;
        cin >> command;
        switch (command.type) {

            case PLAY:
                if (find(legal_moves.begin(), legal_moves.end(), command.card) != legal_moves.end() &&
                        find(hand.begin(), hand.end(), command.card) != hand.end())
                    return command.card;
                cout << "This is not a legal play." << endl;
                break;

            case DISCARD:
                if (legal_moves.size()) {
                    cout << "You have a legal play. You may not discard." << endl;
                    continue;
                }
                throw command.card;
                break;

            case DECK:
                game.printDeck();
                break;

            case QUIT:
                exit(0);

            case RAGEQUIT:
                throw RageQuit();
                break;

            default:
                break;
        }
    }
}
