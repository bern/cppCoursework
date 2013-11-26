/*

	Bernard Marger
	COP3530 Assignment 6
	UFID: 2533-2839
	Section 1085

*/

//check current node. If current node value == object size, insert it
//if not, check whether the current node's value is greater than or less than our object's
//if it's LESS THAN, then check right if you can
//if it's GREATER THAN, then store current node as last best fit (if current node < last best fit) and check left if you can

#include <iostream>
#include <sstream>
#include "BinPacking.h"
#include "MaxWinnerTree.h"
#include "BinarySearchTree.h"

using namespace std;

int* objects;
MaxWinnerTree* m;
BinarySearchTree* s;

void BinPacking::FirstFit(int o[], int n, int binCap) {
	objects = new int[n];
	for(int i = 0; i < n; i++) {
		objects[i] = o[i];
	}
	
	m = new MaxWinnerTree(binCap);
		
	for(int i = 0; i < n; i++) {
		m->insert(objects[i], (i+1));
	}
}

void BinPacking::BestFit(int o[], int n, int binCap) {
	objects = new int[n];
	
	for(int i = 0; i < n; i++) {
		objects[i] = o[i];
	}
	
	s = new BinarySearchTree(binCap);
	
	for(int i = 0; i < n; i++) {
		s->insert(objects[i], (i+1));
	}
}
