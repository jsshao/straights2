#ifndef COMPSTRAT_H
#define COMPSTRAT_H

#include "Strategy.h" 
#include <vector>

// Child class of Strategy
class ComputerStrategy : public Strategy {
public:
    // Implemented virtual function play that simulates computer playstyle
    Card play(const std::vector<Card>& table, const std::vector<Card>& hand, const Game& game) const; 
private:
};

#endif
