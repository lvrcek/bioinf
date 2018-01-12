#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include "Table.h"

/*
 * A constructor for class Table. Hash table is declared as vector of m vectors of integers.
 * Each inner vector represents a bucket, meaning it can store at most same number of elements
 * as is number of slots in a bucket (given with a constant B).
 */

Table::Table() {
    this->hashTable.resize(M);
};

/*
 * A default destructor for class Table.
 */

Table::~Table() = default;

/*
 * A function which takes two arguments: bucket and element.
 *  It returns fingerprint stored at specified bucket and position in bucket (element).
 */

std::bitset<F> Table::getElementFromTable(unsigned int bucketIndex, unsigned int elementIndex) {
    return hashTable.at(bucketIndex).at(elementIndex);
}

/*
 * A function which takes three arguments: bucket, element and value.
 * It sets fingerprint stored in specified bucket at specified element to a given value.
 */

void Table::setElementToTable(unsigned int bucket, unsigned int element, std::bitset<F> value) {
    hashTable.at(bucket).at(element) = value;
}

/*
 * Function which returns a hash table.
 */


std::vector<std::vector<std::bitset<F> > > &Table::getHashTable() {
    return hashTable;
}

/*
 * Function which has one argument, position of bucket in a hash table (bucketNum)
 * and returns bucket which is located at that position in the hash table.
 */


std::vector<std::bitset<F> > &Table::getBucket(int bucketNum) {
    return hashTable.at(bucketNum);
}

size_t Table::getBucketSize(int bucketNum) {
    return hashTable.at(bucketNum).size();
}

void Table::addElementToBucket(std::bitset<F> element, int bucketNum) {
    hashTable.at(bucketNum).push_back(element);
}

/*
 * Function which prints a hash table to the screen.
 */

void Table::printTableToScreen() {
    std::cout << "======HASH TABLE=========\n";
    for (auto &i : hashTable) {
        for (std::bitset<F> j : i) {
            //std::cout << j.to_ulong();	//print as integers
	    std::cout << j;			//print as bitsets
            std::cout << "\t\t";
        }
        std::cout << std::endl;
    }
    std::cout << "=========================\n";
}


