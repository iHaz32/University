// header files
#include "../header/funcs.h"
#include "../header/funcs.h"
#include "../header/Array.h"
#include "../header/AVL.h"
#include "../header/BST.h"
#include "../header/HashTable.h"
#include "../header/SortedArray.h"
#include "../header/funcs.h"
#include "../header/Pair.h"
// libraries
#include <fstream>
#include <string>
#include <cctype>
#include <time.h>


void formatFile(std::string inputFilename, std::string outputFilename) {
    // open input and output files
    std::ifstream inputFile;
    std::ofstream outputFile;
    inputFile.open(inputFilename);
    outputFile.open(outputFilename);
    
    if (inputFile.is_open()){   // make sure there are no errors in opening the file
        // remove punctuation from the text and convert all characters to lowercase
        std::string line;
        while (std::getline(inputFile, line)) {   // loop through each line of the file
            for (char c : line) {   // loop through each character of the line
                if (!std::ispunct(c)) {   // if the character is not punctuation, convert it to lowercase and print it
                    outputFile << (char) std:: tolower(c);
                } else {
                    outputFile << " ";
                }
            }
            outputFile << std::endl;
        }
    } else {
        outputFile << "Error in reading the test file!";
    }

    inputFile.close();
    outputFile.close();
}


Pair* createSet(int& QsetSize) {   // create Q set with random pairs
    srand(time(nullptr));
    QsetSize = rand() % 5000 + 5000;   // random size between 5000 and 10000 

    std::ifstream f;
    f.open("formatted.txt");
    // get size of the file by seeing in which byte the pointer is at the end of the file
    f.seekg(0, std::ios::end);
    int end = f.tellg();   

    Pair* pairs = new Pair[QsetSize];   // create Pair array 

    srand(time(nullptr));   // reset rand seed
    for (int i=0 ; i<QsetSize ; i++) {
        // get random position within the file
        int pos = rand() % end;  
        f.seekg(pos, std::ios::beg);

        std::string word;
        f >> word;   // get rid of word in case pointer is not in suitable position
    
        // create Pair and add it to the array
        f >> word;
        pairs[i].word1 = word;
        f >> word;
        pairs[i].word2 = word;
    }
    f.close();

    return pairs;
}

// call data structures
void array(std::string filename, Pair* Qset, int QsetSize) {
    std::cout << "Started creating the array..." << std::endl;
    Array array;
    array.showResults("formatted.txt", Qset, QsetSize); 
    std::cout << "Finished creating the array..." << std::endl; 
}

void sortedArray(std::string filename, Pair* Qset, int QsetSize) {
    std::cout << "Started creating the sorted array..." << std::endl;
    SortedArray sortedArray;
    sortedArray.showResults("formatted.txt", Qset, QsetSize);
    std::cout << "Finished creating the sorted array..." << std::endl;
}

void binarySearchTree(std::string filename, Pair* Qset, int QsetSize) {
    std::cout << "Started creating the BST..." << std::endl;
    BST bst;
    bst.showResults("formatted.txt", Qset, QsetSize);
    std::cout << "Finished creating the BST..." << std::endl;
}

void avlTree(std::string filename, Pair* Qset, int QsetSize) {
    std::cout << "Started creating the AVL..." << std::endl;
    AVL avl;
    avl.showResults("formatted.txt", Qset, QsetSize);
    std::cout << "Finished creating the AVL..." << std::endl;
}

void hashTable(std::string filename, Pair* Qset, int QsetSize) {
    std::cout << "Started creating the Hashtable..." << std::endl;
    HashTable hashtable;
    hashtable.showResults("formatted.txt", Qset, QsetSize);
    std::cout << "Finished creating the Hashtable..." << std::endl;
}

int max(int a, int b) {
    return a>b?a:b;
}