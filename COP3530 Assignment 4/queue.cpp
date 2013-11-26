#include <iostream>
#include <sstream>
#include "Myexception.h"
#include "queue.h"

using namespace std;

arrayList* list;

queue::queue(int initialCapacity) {
	list = new arrayList(initialCapacity);
}

queue::~queue() {
	delete list;
}

void queue::emptyQueue() {
	while(!list -> empty()) 
		pop();
}

int queue::getSize() const {
	return list -> size();
}

void queue::push(const int& item) {
	list -> insert(0, item);
}

void queue::pop() {
	list -> erase(getSize()-1);		
}

int& queue::front() {
	return *(list -> get(0));
}

int& queue::back() {
	return *(list -> get(getSize()-1));
}
