#include <iostream>       // output
#include <algorithm>
#include <vector>
#include "PRNG.h"
#include "q2printer.h"
#include "q2player.h"
using namespace std;

PRNG prng;

Printer::Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards ) {
    // Initialize cards in players' hands
    cards.resize(NoOfPlayers, make_pair(-1,-1)); 
    totCards = NoOfCards;
}

// This function writes out the sequence of plays in the buffer
void Printer::flush( const unsigned int id, unsigned int PlayersRemaining) {
    cout << endl;
    for (size_t i = 0; i < cards.size(); i++) {
        // Ignore players who did not play any cards
        if (cards[i].first != -1) {
        
            // Win by being last player remaining    
            if (PlayersRemaining == 1 && i == id && cards[i].first == 0)
                cout << '#' << cards[i].first + cards[i].second << '#';
            else {
                cout << cards[i].first << ':' << cards[i].second;
                // Win by taking remaining cards
                if (totCards == 0 && i == id)
                    cout << '#';
                else {
                    cout << (cards[i].second % 2 == 0 ? '>' : '<');
                    if (i == id)
                        cout << '*';
                }
            }

            if ((cards[i].first + cards[i].second) % Player::DEATH_DECK_DIVISOR == 0)
                cout << 'X';
        }
        cout << '\t';
    }
}

void Printer::prt( const unsigned int id, const unsigned int took, unsigned int PlayersRemaining ) {
    // Flush buffer if player already has previously made a play already
    if (cards[id].first != -1) {
        flush(id, PlayersRemaining);
        fill(cards.begin(), cards.end(), make_pair(-1,-1)); 
    }

    totCards -= took;
    cards[id] = make_pair(took, totCards);

    // Flush buffer on winning condition
    if (PlayersRemaining == 1 || totCards == 0)
        flush(id, PlayersRemaining);
}

Player::Player( Printer &printer, unsigned int id ) : print(printer), playerId(id) {};

void Player::main() {
    suspend();
    for ( ;; ) {
        // Game is over if there is only one player remaining
        if (totPlayers == 1) {
            print.prt( playerId, 0, 1);
            break;
        }

        int cardsTaken = prng(1, 8);
        if (cardsTaken > deckCards)
            cardsTaken = deckCards;

        print.prt( playerId, cardsTaken, totPlayers );
        
        // Game is over if this player took the remaining cards
        if (deckCards - cardsTaken == 0)
            break;

        if (deckCards % DEATH_DECK_DIVISOR == 0) {
            totPlayers -= 1;

            leftPlayer->rightPlayer = rightPlayer;
            rightPlayer->leftPlayer = leftPlayer;
        }

        if ( (deckCards - cardsTaken) % 2 == 0 )
            rightPlayer->play(deckCards - cardsTaken);
        else
            leftPlayer->play(deckCards - cardsTaken);
    }
}

void Player::players( unsigned int num ) { 
    totPlayers = num;
}

void Player::start( Player &lp, Player &rp ) {
    leftPlayer = &lp;
    rightPlayer = &rp;
    resume();
}

void Player::play( unsigned int deck ) {
    deckCards = deck;
    resume();
}

// Helper function to print error message for incorrect use
void usage(char *exec) {
    cerr << "Usage: " << exec << " [ games (>= 0) [ random-seed ] ]" << endl;  
    exit( EXIT_FAILURE );
}

/*
   This function converts a string to an integer. If part of the string is not a
   valid string, an exception is thrown. A minimum value is also passed in to
   throw an exception if the converted integer is smaller than what's allowed.
 */
uint32_t convertStringToInt(char *str, int min) {
    int result;
    size_t processed_char;

    result = stoi(str, &processed_char);
    if (processed_char != strlen(str) || result < min)
        throw invalid_argument("Not an integer or value too large");

    return result;
}

void uMain::main() {
    uint32_t seed = getpid();
    uint32_t games = 5;
    switch ( argc ) {
        case 3:
            try {
                seed = convertStringToInt(argv[2], 1);
            } catch ( invalid_argument &e ) {
                usage(argv[0]);
            }
            // FALL THROUGH
        case 2:
            try {
                games = convertStringToInt(argv[1], 0);
            } catch ( invalid_argument &e ) {
                usage(argv[0]);
            }
            break;
        default:
            usage(argv[0]);
    }

    prng.seed(seed);
    for (size_t game_index = 0; game_index < games; game_index++) {
        // Initial values for a game
        int num_players = prng( 2, 10 );
        int start_deck = prng(10, 200);
        int start_player = prng( 0, num_players - 1 );
        Printer print(num_players, start_deck);
        Player* players[num_players];

        cout << "Players: " << num_players << "    Cards: " << start_deck << endl;

        for (int i = 0; i < num_players; i++) {
            Player *new_player = new Player(print, i);
            players[i] = new_player;
            cout << "P" << i << '\t';
        }

        Player::players(num_players); // Initialize number of players
        
        // Set each players' left/right players
        for (int i = 0; i < num_players; i++) {
            players[i]->start(*players[(i - 1 + num_players) % num_players], *players[(i + 1 + num_players) % num_players]); 
        }

        players[start_player]->play(start_deck);

        // Delete the players after game finishes
        for (int i = 0; i < num_players; i++)
            delete players[i];

        if (game_index != games - 1)
            cout << endl << endl;
        cout << endl;
    }
}
