#include <cstdio>
#include <cstdlib>
#include "Game.h"

// Main class to start up the game of Straights 
int main(int argc, char* argv[]) {
    // If command line argument is passed, seed the RNG with the argument
    if (argc > 1) {
        srand48(atoi(argv[1]));
    } else {
        srand48(0);
    }

    // Start the game
    Game newGame;
    newGame.start();

    return 0;
}
