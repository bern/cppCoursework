/*

	Bernard Marger
	COP3530 Assignment 6
	UFID: 2533-2839
	Section 1085

*/

#include <iostream>
#include "MaxWinnerTree.h"
#ifndef BTREE
#define BTREE
#include "BinaryTree.h"
#endif

using namespace std;

BinaryTree* b;
BinaryTreeNode* bin;
int* binAmount;
int bCap;
int height;

MaxWinnerTree::MaxWinnerTree(int cap) {
	bCap = cap;
	b = new BinaryTree(bCap);
	height = 1;
}

MaxWinnerTree::~MaxWinnerTree() {
}

void MaxWinnerTree::replay(BinaryTreeNode* node) {
	if(node -> key == 0) {
		replay(node->left);
		replay(node->right);
		if(node->left->value >= node->right->value) {
			node->changeValue(node->left->value);
		}
		else if(node->left->value < node->right->value) {
			node->changeValue(node->right->value);
		}
	}
}

void MaxWinnerTree::insert(int n, int objectNum) {
	bin = new BinaryTreeNode(0,0);
	find(b->root, n);
	if(bin->value != 0) {
		cout << "Pack object " << objectNum << " in bin " << bin->key << endl;
		bin->addItem(n);
		replay(b->root);
	}
	else {
		b->setKey(1);
		expand();
		replay(b->root);
		height++;
		insert(n, objectNum);
	}
}

void MaxWinnerTree::fillBinArray(BinaryTreeNode* node, int n) {
	if(node->key==0) {
		fillBinArray(node->left, n);
		fillBinArray(node->right, n);
	}
	else {
		int index = 0;
		for(int i = 0; i < n; i++) {
			if (binAmount[i] == bCap) {
				index = i;
				break;
			}
		}
		binAmount[index] = node->value;
		node->changeKey(-1);
	}
}

void MaxWinnerTree::expand() {
	int arrSize = 1;
	int temp = height;
	while(temp > 0) {
		arrSize*=2;
		temp--;
	}
	binAmount = new int[arrSize];
	for(int i = 0; i < arrSize; i++) {
		binAmount[i] = bCap;
	}
	fillBinArray(b->root, arrSize);
	expandTree(b->root, 0, arrSize);
}

void MaxWinnerTree::expandTree(BinaryTreeNode* node, int index, int arrSize) {
	int x = 0;
	if(node->key!=-1) {
		expandTree(node->left, index, arrSize);
		expandTree(node->right, index, arrSize);
	}
	else {
		if(b->curKey >= arrSize) {
			node->setLeft(new BinaryTreeNode(b->curKey, bCap));
		}
		else {
			node->setLeft(new BinaryTreeNode(b->curKey, binAmount[b->curKey-1]));
		}
		index++;
		b->nextKey();
		if(b->curKey >= arrSize) {
			node->setRight(new BinaryTreeNode(b->curKey, bCap));
		}
		else {
			node->setRight(new BinaryTreeNode(b->curKey, binAmount[b->curKey-1]));
		}
		b->nextKey();
		index++;
		node->changeValue(-1);
		node->changeKey(0);
	}
}

void MaxWinnerTree::find(BinaryTreeNode* node, int objectSize) {
	if(node->key==0) {
		if(node->left->value >= objectSize)
			find(node->left, objectSize);
		else
			find(node->right, objectSize);
	}
	if(node->key != 0 && node->value >= objectSize) {
		bin = node;
		return;
	}
}
