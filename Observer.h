#ifndef OBSERVER_H
#define OBSERVER_H

// Abstract observer class with pure virtual update function
class Observer {
public:
	virtual void update() = 0;
};

#endif
