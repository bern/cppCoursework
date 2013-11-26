/*

	Bernard Marger
	COP3530 Assignment 5
	UFID: 2533-2839
	Section 1085

*/

#ifndef ARRLIST
#define ARRLIST
#include "Arraylist.h"
#endif

using namespace std;

class BinaryTree : public arrayList {
	public:
		arrayList* a;
		BinaryTree();
		BinaryTree(arrayList* a);
		int size;
		~BinaryTree();
		void inOrder(int i);
		void preOrder(int i);
		void postOrder(int i);
		bool empty() {return size == 0;}
};
