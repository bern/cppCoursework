/*

	Bernard Marger
	COP3530 Assignment 6
	UFID: 2533-2839
	Section 1085

*/

#include <iostream>
#include "BinPacking.h"

using namespace std;

int main() {
	char choice = ' '; int n = 0; int binCap = 0;
	cout << "Welcome to the bin-packing simulator!" << endl;
	do {
		cout << "\nPlease choose the algorithm for test:\n\n1. First Fit\n2. Best Fit\n3. Quit\n\nChoice: ";
		cin >> choice;
		if(choice!='3'&&choice!='2'&&choice!='1') {
			cout << "Invalid choice! Try again." << endl;
		}
		else if (choice == '3') {
			cout << "Quitting now." << endl;
		}
		else {
			cout << "Enter the number of objects and the bin capacity for your ";
			if(choice == '1') cout << "first fit ";
			if(choice == '2') cout << "best fit ";
			cout << "simulation\n\n";
			cout << "Number of objects: ";
			cin >> n;
			cout << "Bin capacity: ";
			cin >> binCap;
			
			int objects[n];
			
			for(int i = 0; i < n; i++) {
				cout << "Enter the size of object " << (i+1) << ": ";
				cin >> objects[i];
			}
			
			cout << endl;
			
			BinPacking* sim = new BinPacking();
			
			if(choice == '1') sim->FirstFit(objects, n, binCap);
			if(choice == '2') sim->BestFit(objects, n, binCap);
		}
	} while(choice != '3');
	
	return 0;
}
