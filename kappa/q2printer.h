#ifndef __Q2PRINTER_H__
#define __Q2PRINTER_H__

#include <vector>

using namespace std;

class Printer {
    vector< pair<int, int> > cards;   // first in pair is cards played, second is deck size afterwards
    int totCards;
    void flush( const unsigned int id, unsigned int PlayersRemaining);
  public:
    Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards );
    void prt( const unsigned int id, const unsigned int took, unsigned int PlayersRemaining );
};
#endif
