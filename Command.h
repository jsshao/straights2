#ifndef _COMMAND_
#define _COMMAND_

#include "Card.h"
#include <istream>

// Enum type definition of legal commands
enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command{
	// A command composes of a command type and a card
    Type type;
	Card card;
	
	Command() : type(BAD_COMMAND), card(SPADE, ACE) {}
};

// Overloaded stream extraction operator
std::istream &operator>>(std::istream &, Command &);

#endif
