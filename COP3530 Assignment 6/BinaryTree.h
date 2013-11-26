/*

	Bernard Marger
	COP3530 Assignment 6
	UFID: 2533-2839
	Section 1085

*/
#include <iostream>

using namespace std;

struct BinaryTreeNode {
	public:
		BinaryTreeNode* left;
		BinaryTreeNode* right;
		BinaryTreeNode* parent;
		int value;
		int key;
		BinaryTreeNode(int k, int v) {
			value = v;
			key = k;
			left = NULL;
			right = NULL;
			parent = NULL;
		}
		void setLeft(BinaryTreeNode* l) {
			left = l;
			l -> parent = this;
		}
		void setRight(BinaryTreeNode* r) {
			right = r;
			r -> parent = this;
		}
		void setParent(BinaryTreeNode* p) {
			parent = p;
		}
		void addItem(int size) {
			value -= size;
		}
		void changeValue(int v) {
			value = v;
		}
		void changeKey(int k) {
			key = k;
		}
};

class BinaryTree {
	public:
		int curKey;
		BinaryTreeNode* root;
		BinaryTree(int binCap);
		void nextKey() {
			curKey++;
		}
		void setRoot(BinaryTreeNode* node) {
			root = node;
		}
		void setKey(int n) {
			curKey = n;
		} 
		~BinaryTree();
};
