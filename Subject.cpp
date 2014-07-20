#include <set>
#include "Subject.h"

// Subscribe to the observer
void Subject::subscribe (Observer *view) {
	observers_.insert(view);
}

// Unsubscribe to the observer
void Subject::unsubscribe (Observer *view) {
	observers_.erase(view);
}

// Notify all observers to be updated
void Subject::notify() {
	std::set<Observer*>::iterator i;
	for (i = observers_.begin(); i != observers_.end(); i++) {
		(*i)->update();
	}
}
