#include <set>
#include "Subject.h"

void Subject::subscribe (Observer *view) {
	observers_.insert(view);
}

void Subject::unsubscribe (Observer *view) {
	observers_.erase(view);
}

void Subject::notify() {
	std::set<Observer*>::iterator i;
	for (i = observers_.begin(); i != observers_.end(); i++) {
		(*i)->update();
	}
}
