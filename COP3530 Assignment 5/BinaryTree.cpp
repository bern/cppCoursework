/*

	Bernard Marger
	COP3530 Assignment 5
	UFID: 2533-2839
	Section 1085

*/

//This BinaryTree class acts as a barebones skeleton for the MinHeap.
//It is essentially an arrayList with the added functionality of the orders.

#include <iostream>
#include <sstream>
#include "Myexception.h"
#include "BinaryTree.h"

using namespace std;

arrayList* a;

BinaryTree::~BinaryTree() {
}

BinaryTree::BinaryTree() {
	a = NULL;
}

BinaryTree::BinaryTree(arrayList* arr) {
	a = arr;
}

//The only difference between the three orderings is the spot in which the cout statement appears
//Relative to the structure of if-statements. Pre (before the if statements) order, 
//In (within the if statements) order, and Post (after the if statements) order

void BinaryTree::preOrder(int i) {
	int left = (2*i)+1;
	int right = (2*i)+2;
	cout << *(a -> get(i)) << " "; 
	if (left < a -> size()) 
		preOrder(left); 
	if (right < a -> size()) 
		preOrder(right); 
}

void BinaryTree::inOrder(int i) {
	int left = (2*i)+1;
	int right = (2*i)+2;
	if (left < a -> size()) 
		inOrder(left);
	cout << *(a -> get(i)) << " "; 
	if (right < a -> size()) 
		inOrder(right);
	return;
}

void BinaryTree::postOrder(int i) {
	int left = (2*i)+1;
	int right = (2*i)+2;
	if (left < a -> size()) 
		postOrder(left); 
	if (right < a -> size()) 
		postOrder(right);
	cout << *(a -> get(i)) << " "; 
}
