//header files
#include "../header/funcs.h"
#include "../header/Pair.h"

//libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

// arguments (chosen file to format and numbers from 1 to 5)
int main(int argc, char *argv[]) {   
	formatFile(argv[1], "formatted.txt");   // format the text file
	
	// create Q set with random search to be searched
	int QsetSize;   
	Pair* Qset = createSet(QsetSize);   // pass QsetSize by reference to get its value as it will be random

	// each integer from 1-5 represents a data structure
	for (int i=2 ; i<argc ; i++) {
		std::string ds = argv[i];
		if (ds == "1") {
			array("formatted.txt", Qset, QsetSize);   // call Array
		} else if (ds == "2") {
			sortedArray("formatted.txt", Qset, QsetSize);   // call Sorted Array
		} else if (ds == "3") {
			binarySearchTree("formatted.txt", Qset, QsetSize);   // call Binary Search Tree
		} else if (ds == "4") {
			avlTree("formatted.txt", Qset, QsetSize);   // call AVL tree
		} else if (ds == "5") {
			hashTable("formatted.txt", Qset, QsetSize);   // call Hashtable
		}
	}
	
	return 0;
}
