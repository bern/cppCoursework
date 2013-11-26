/*

	Bernard Marger
	COP3530 Assignment 5
	UFID: 2533-2839
	Section 1085

*/

#include <iostream>
#include <sstream>
#include "Myexception.h"
#include "PriorityQueue.h"

using namespace std;

MinHeap* heap;

//Initialize the heap, yo!
void PriorityQueue::initialize(arrayList* arr, int capacity) {
	heap = new MinHeap(arr, capacity);
}

//Alternation top and pop until the heap is empty
void PriorityQueue::sort() {
	while(!heap -> isEmpty()) {
		cout << heap -> top() << " ";
		heap -> pop();
	}
}

void PriorityQueue::inOrder(int i) {
	heap -> b -> inOrder(i);
}

void PriorityQueue::preOrder(int i) {
	heap -> b -> preOrder(i);
}

void PriorityQueue::postOrder(int i) {
	heap -> b -> postOrder(i);
}

