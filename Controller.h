#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "gtkmm.h"

// The controller class as part of MVC model for Straights game

class Controller {
public:
	// Constructor
	Controller(Model *);

	// Destructor
	~Controller();
	
	// Seed mutator
	void setSeed(const long);
	
	// Start and End game controls
	void startGame();
	void endGame();

	// Play a card
	void selectCard(int);

	// Switch between human/computer player
	void togglePlayerType(int);

private:
	// Member Model
	Model *model_;
};

#endif
