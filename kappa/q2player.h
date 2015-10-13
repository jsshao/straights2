#ifndef __Q2PLAYER_H__
#define __Q2PLAYER_H__

#include "q2printer.h"

using namespace std;

_Coroutine Player {
    Player* leftPlayer;
    Player* rightPlayer;
    Printer &print;
    static int totPlayers;
    int playerId;
    int deckCards;
    void main();

  public:
    enum { DEATH_DECK_DIVISOR = 5 };
    static void players( unsigned int num );
    Player( Printer &printer, unsigned int id );
    void start( Player &lp, Player &rp );
    void play( unsigned int deck );
};

int Player::totPlayers = 0;
#endif
