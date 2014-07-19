#include "Controller.h"
#include "Model.h"

Controller::Controller(Model *model) : model_(model) {}

Controller::~Controller() {
	if (model_ != NULL) {
		delete model_;
	}
}

void Controller::setSeed(const long seed) {
	model_->setSeed(seed);
}

void Controller::startGame() {
	model_->startGame();
}

void Controller::endGame() {
	model_->endGame();
}

void Controller::selectCard(int index) {
	
}

void Controller::togglePlayerType(int player) {
	model_->togglePlayerType(player);
}

