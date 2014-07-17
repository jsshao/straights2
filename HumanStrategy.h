#ifndef HUMANSTRAT_H
#define HUMANSTRAT_H

#include "Strategy.h" 
#include "Card.h"
#include <vector>

class HumanStrategy : public Strategy {
public:
    // Implement virtual function that simulates human player's strategy (user input)
    Card play(const std::vector<Card>& table, const std::vector<Card>& hand, const Game& game) const; 
private:
};

#endif
