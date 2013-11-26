#include <iostream>
#include <sstream>
#include "Myexception.h"
#include "stack.h"

using namespace std;

arrayList* elements;

stack::stack(int initialCapacity) {
	elements = new arrayList(initialCapacity);
}

stack::~stack() {
	delete elements;
}

void stack::emptyStack() {
	while(!elements -> empty()) 
		pop();
}

int stack::getSize() const {
	return elements -> size();
}

void stack::push(const int& item) {
	elements -> insert(getSize(), item);
}

void stack::pop() {
	elements -> erase(getSize()-1);	
}

int& stack::top() {
	return *(elements -> get(getSize()-1));
}
