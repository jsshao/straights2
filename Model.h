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
	bool isPlayerComputer(const int player) const;
	std::vector<int> getScores() const;
	std::vector<int> getWinners() const;
	int startingPlayer() const;
    bool gameStarted() const;
    int currentPlayer() const;
    std::vector<Card> getTable() const;
    std::vector<Card> getCurHand() const;
    void selectCard(int); 
	
private:
	int turn_;
	bool isComputer_[numOfPlayers];
	long seed_;
    std::vector<int> winners_;
	Game *newGame;
};

#endif
