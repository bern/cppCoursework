#ifndef ARRLIST
#define ARRLIST
#include "Arraylist.h"
#endif

using namespace std;

class stack : public arrayList {
	protected:
		arrayList* elements;
		
	public:
		stack(int initialCapacity);
		 ~stack();
		bool empty() {return elements -> empty();}
		int getSize() const;
		void push(const int& item); //elements.add(item);
		void pop(); //elements -> remove(elements -> size()-1));
		int& top(); //return (elements -> get(elements -> size()-1));
		void emptyStack();
};

