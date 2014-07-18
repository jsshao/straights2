#include <set>
#include "subject.h"
#include "observer.h"

void Subject::subscribe (Observer *view) {
	observers_.insert(view);
}

void Subject::unsubscribe (Observer *view) {
	observers_.erase(view);
}

void Subject::notify() {
	std::set<Observers*>::iterator i;
	for (i = observers_.begin(); i != observers_.end(); i++) {
		(*i)->update();
	}
}
