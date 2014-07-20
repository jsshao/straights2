#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include "Observer.h"

// Implementation of the Subject in the Observer patter

class Subject {
public:
	//Subscribe and unsubscribe to observers
	void subscribe(Observer*);
	void unsubscribe(Observer*);
protected:
	// Notify all observers of changes
	void notify();
private:
	// Set of all observer pointers
	std::set<Observer*> observers_;		
};
#endif
