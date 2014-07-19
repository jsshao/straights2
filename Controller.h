#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "gtkmm.h"

class Controller {
public:
	Controller(Model *);
	~Controller();
	void setSeed(const long);
	void startGame();
	void endGame();
	void selectCard(int);
	void togglePlayerType(int);

private:
	Model *model_;
}

#endif
