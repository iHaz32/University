#include "../header/Array.h"
#include <chrono>
#include <iostream>
#include <fstream>

// constructor
Array:: Array() {
    capacity = 262144;
    data = new Pair[capacity]; 
    size = 0;
    constTime = 0;
    searchTime = 0;
}

// destructor
Array:: ~Array() {
    capacity = 0;
    size = 0;
    delete []data;   // delete array and set capacity to 0
}

// methods

// double the array's capacity dynamically
void Array:: doubleCapacity() {
    // create new array with double the current capacity
    Pair* temp = new Pair[capacity*2];

    // copy all of the current array's pairs
    for (int i=0 ; i<size ; i++) {
        temp[i] = data[i];
    }

    // delete old array and replace it with the new one
    delete []data;
    data = temp;
    capacity = 2*capacity;
}

// create the pairs from the text file
void Array:: createPairs(std::string filename) {
    std::ifstream file;
    file.open(filename);
    
    if (file.is_open()) {
        auto startConstructing = std::chrono::high_resolution_clock::now();   // track start time of constructing
        std::string word;
        Pair* tempPair = new Pair;

        // start creating the pairs
        file >> word;
        // create temporay pair
        tempPair->word1 = word;
        while (file) {
            file >> word;
            tempPair->word2 = word;
            handlePair(tempPair);   // place tempPair in array or increase appearances if it already exists
            tempPair->word1 = word;   
        }
        delete tempPair;   // free memory
        
        auto endConstructing = std::chrono::high_resolution_clock::now();   // track end time of constructing
        std::chrono::duration<double> duration = endConstructing - startConstructing;   // calculate duration of constructing
        this->constTime = duration.count();   // assign duration

        file.close();

        std::ofstream output;
        output.open("results/Array.txt");
        output << "Time to create " << size << " pairs for Array: " << this->constTime << " seconds." << std::endl;
    } else {
        std::cerr << "Error! file not found..." << std::endl;
    }
}
 
// search pairs from Q set with linear search
void Array:: searchPairs(Pair* Qset, int QsetSize) {
    auto startSearching = std::chrono::high_resolution_clock::now();   // track start time of searching 

    for (int i=0 ; i<QsetSize ; i++) {
        bool found = false;
        for (int j=0 ; j<size && !(found) ; j++) {
            if (data[j] == Qset[i]) {
                Qset[i].apps = data[j].apps;
                found = true;   
            }
        } 
    }

    auto endSearching = std::chrono::high_resolution_clock::now();   // track end time of searching 
    std::chrono::duration<double> duration = endSearching - startSearching;   // calculate duration of searching 
    searchTime = duration.count();

    std::ofstream output;
    output.open("results/Array.txt", std::ios::app);   // append from previous pointer position
    output << "Time to search " << QsetSize << " pairs for Array: " << searchTime << " seconds." << std::endl;   // print searching time

    output << std::endl << "Pairs and their number of appearances:" << std::endl;
    for (int i=0 ; i<QsetSize ; i++) {   
        output << Qset[i] << std::endl;   // print pairs and their appearances
    }
}

// add pair to data if not already included, otherwise increase appearances
void Array:: handlePair(Pair* tempPair) {
    bool alreadyExists = false;
    for (int i=0 ; i<size && !(alreadyExists) ; i++) {
        if (data[i] == *tempPair) {
            alreadyExists = true;
            data[i].apps++;
        }
    }
    if (!alreadyExists) {
        if (size >= capacity)
            doubleCapacity();
        data[size] = *tempPair;
        data[size].apps = 1;
        size++;
    }
}

void Array:: showResults(std::string filename, Pair* Qset, int QsetSize) {
    createPairs(filename);
	searchPairs(Qset, QsetSize); 
}