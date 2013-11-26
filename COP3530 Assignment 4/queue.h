#ifndef ARRLIST
#define ARRLIST
#include "Arraylist.h"
#endif

using namespace std;

class queue : public arrayList {
	protected:
		arrayList* list;
		
	public:
		queue(int initialCapacity);
		~queue();
		bool empty() {return list -> empty();}
		int getSize() const;
		void push(const int& item); //list.add(item);
		void pop(); //list -> remove(list -> size()-1));
		int& front(); //return (list -> get(list -> size()-1));
		int& back();
		void emptyQueue();
};
