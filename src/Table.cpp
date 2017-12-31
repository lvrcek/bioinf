#include <string>
#include <iostream>
#include <vector>
#include "Table.h"

/*
 * A constructor for class Table. Table is initialised as matrix of m rows
 * and m columns. Matrix is implemented as vector containing vectors of integers.
 */

Table::Table(unsigned int m) {
    std::vector<std::vector<int> > matrix(m);
    this->hashTable = matrix;
};

/*
 * A default destructor for class Table.
 */

Table::~Table() = default;

/*
 * A function which takes two arguments: bucket and element.
 *  It returns fingerprint stored at specified bucket and position in bucket (element).
 */

int Table::getElementFromTable(unsigned int bucket, unsigned int element) {
    return hashTable.at(bucket).at(element);
}

/*
 * A function which takes three arguments: bucket, element and value.
 * It sets fingerprint stored in specified bucket at specified element to a given value.
 */

void Table::setElementToTable(unsigned int bucket, unsigned int element, int value) {
    hashTable.at(bucket).at(element) = value;
}

/*
 * Function which returns a hash table.
 */


std::vector<std::vector<int> > &Table::getHashTable() {
    return hashTable;
}

/*
 * Function which has one argument, position of bucket in a hash table (bucketNum)
 * and returns bucket which is located at that position in the hash table.
 */


std::vector<int> &Table::getBucket(int bucketNum) {
    return hashTable.at(bucketNum);
}

/*
 * Function which prints a hash table to the screen.
 */

void Table::printTableToScreen() {
    std::cout << "======HASH TABLE=========\n";
    for (auto &i : hashTable) {
        for (int j : i) {
            std::cout << j;
            std::cout << "\t\t";
        }
        std::cout << std::endl;
    }
    std::cout << "=========================\n";
}


