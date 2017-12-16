#include <string>
#include <iostream>
#include <vector>
#include "Table.h"

Table::Table(uint m, uint b) {
    std::vector<std::vector<int>> matrix(m, std::vector<int>(b, 0));
    this->hashTable = matrix;
};

Table::~Table() = default;

int Table::getElementFromTable(uint bucket, uint element) {
    return hashTable.at(bucket).at(element);
}

void Table::setElementToTable(uint bucket, uint element, int value) {
    hashTable.at(bucket).at(element) = value;
}

std::vector<std::vector<int>> &Table::getHashTable() {
    return hashTable;
}

std::vector<int> &Table::getBucket(int bucketNum) {
    return hashTable.at(bucketNum);
}

void Table::printTableToScreen() {
    for (auto &i : hashTable) {
        for (int j : i) {
            std::cout << j;
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}



