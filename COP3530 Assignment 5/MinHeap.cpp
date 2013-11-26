/*

	Bernard Marger
	COP3530 Assignment 5
	UFID: 2533-2839
	Section 1085

*/

#include <iostream>
#include <sstream>
#include "Myexception.h"
#include "MinHeap.h"

using namespace std;

BinaryTree* b;

MinHeap::MinHeap() {
	b = NULL;
}

MinHeap::MinHeap(arrayList* arr, int capacity) {
	//Creates the MinHeap using the heapify function
	
	b = new BinaryTree(arr);
	
	for(int i = ((b -> a -> size())-1); i >= 0; i--) {
		heapify(i);
	}
}

MinHeap::~MinHeap() {
}

//Push something onto the heap
void MinHeap::push(int x) {
	int store = b -> a ->size();
	
	//Since we're using an arrayList representation, add an extra node containing element x
	
	b -> a ->insert(store, x);
	
	//As long as the node we're looking at (initially the node with element x)
	//is smaller than its parent (location of x/2), swap them and look at the parent next
	
	while(*(b -> a ->get(store)) < *(b -> a ->get(store/2))) {
		int parent = *(b -> a ->get(store/2));
		b -> a ->changeValue((store/2), *(b -> a ->get(store)));
		b -> a ->changeValue((store), parent);
		store = store/2; 
	}
}

//Performs heap sort on an array
void MinHeap::heapify(int i) {
	
	int left = (2*i)+1;
	int right = (2*i)+2;
	int length = b -> a ->size();

	int smallest = i;
	
	//Determines the smallest child of a given node (i)
	
	if(left < length && (*(b -> a ->get(left)) < *(b -> a ->get(smallest)))) {
		smallest = left;
	}
	if(right < length && (*(b -> a ->get(right)) < *(b -> a ->get(smallest)))) {
		smallest = right;
	}
	
	//If the smallest child is smaller than the given node (i),
	//Swap the two and send the smaller child's index to the heapify function
	
	if(smallest != i) {
		int temp = *(b -> a ->get(i));
		b -> a ->changeValue(i, *(b -> a ->get(smallest)));
		b -> a ->changeValue(smallest, temp);
		heapify(smallest);
	}
	
	return;
}

void MinHeap::pop(){
	
	//Make the last element of the heap the root node
	//Heapify the root
	
	b -> a ->changeValue(0, *(b -> a ->get(b -> a ->size()-1)));
	b -> a ->erase(b -> a ->size()-1);
	heapify(0);
}
