/*

	Bernard Marger
	COP3530 Assignment 3
	UFID: 2533-2839
	Section 1085

*/

#include "ChainNode.h"
#include "Linearlist.h"

using namespace std;

class chain : public linearList{
	protected:
		ChainNode* firstNode;
		int listSize;
		virtual void checkIndex(int index) const;
		
	public:
		chain(int initialCapacity);
		virtual ~chain();
      	virtual bool empty() const {return listSize == 0;}
      	virtual int size() const {return listSize;}
      	virtual int* get(int theIndex) const;
      	virtual int indexOf(const int& theElement)const;
      	virtual void erase(int theIndex);
      	virtual void insert(int theIndex, const int& theElement);
		virtual void traverse();
	 	virtual void MaxMin();
};
