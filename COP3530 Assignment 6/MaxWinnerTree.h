/*

	Bernard Marger
	COP3530 Assignment 6
	UFID: 2533-2839
	Section 1085

*/

#ifndef BTREE
#define BTREE
#include "BinaryTree.h"
#endif

using namespace std;

class MaxWinnerTree {
	public:
		int* binAmount;
		MaxWinnerTree(int binCap);
		~MaxWinnerTree();
		void replay(BinaryTreeNode* node);
		void expand();
		void insert(int n, int objectNum);
		void fillBinArray(BinaryTreeNode* node, int n);
		void expandTree(BinaryTreeNode* node, int index, int arrSize);
		void find(BinaryTreeNode* node, int objectSize);
};
