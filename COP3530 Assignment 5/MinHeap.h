/*

	Bernard Marger
	COP3530 Assignment 5
	UFID: 2533-2839
	Section 1085

*/

#ifndef BTREE
#define BTREE
#include "BinaryTree.h"
#endif


using namespace std;

class MinHeap : public BinaryTree {
	public:
		BinaryTree* b;
		MinHeap ();
		MinHeap (arrayList* arr, int capacity);
		~MinHeap();
		void push(int x);
		int& top() {return *(b -> a -> get(0));};
		void heapify(int i);
		void pop();
		bool isEmpty() {return (b -> a -> empty());};
		void print();
};
