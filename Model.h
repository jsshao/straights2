#ifndef MODEL_H
#define MODEL_H

#include "Subject.h"
#include "Game.h"

const int numOfPlayers = 4;

class Model : public Subject {
public:
	Model();
	~Model();
	void startGame();
	void endGame();
	void setSeed(const long seed);
	void togglePlayerType(const int player);
	bool isPlayerComputer(const int player);
	std::vector<int> getScores();
	std::vector<int> getWinners();
	int startingPlayer();
	
private:
	int turn;
	bool isComputer_[numOfPlayers];
	long seed_;
    std::vector<int> winners_;
	Game *newGame;
};

#endif
