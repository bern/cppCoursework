/*

	Bernard Marger
	COP3530 Assignment 5
	UFID: 2533-2839
	Section 1085

*/

#ifndef MINHEAP
#define MINHEAP
#include "MinHeap.h"
#endif

using namespace std;

class PriorityQueue : MinHeap {
	protected:
		MinHeap* heap;
		
	public:
		PriorityQueue() {heap = new MinHeap();};
		void initialize(arrayList* arr, int capacity);
		void inOrder(int i);
		void preOrder(int i);
		void postOrder(int i);
		void sort();
};
