#ifndef RAGEQUIT_H
#define RAGEQUIT_H

#include <exception>

// Create a RageQuit exception
class RageQuit: public std::exception {
public:
    const char* what() const throw ();
private:
};

#endif
