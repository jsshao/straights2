#include "RageQuit.h"

// Implementation of RageQuit Exception
const char* RageQuit::what() const throw () {
    return "Someone ragequit!";
}
