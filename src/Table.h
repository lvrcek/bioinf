#ifndef BIOINF_TABLE_H
#define BIOINF_TABLE_H

#include <vector>
#include <bitset>
#include "Constants.h"
#include <set>
#include "BucketTable.cpp"



/*
 * Declaration of class Table which represents
 * a cuckoo table in which fingerprints are stored.
 */



class Table {
public:
    explicit Table();

    ~Table();

    int getElementFromTable(unsigned int bucketIndex, unsigned int elementIndex);

    void setElementToTable(unsigned int bucket, unsigned int element, int value);

    std::vector<int> &getHashTable();

    std::vector<int> getBucket(int bucketNum);

    size_t getBucketSize(int bucketNum);

    void addElementToBucket(int element, int bucketNum);

    void printTableToScreen();

    int lookUpEntry(int element, int bucketIndex);

    void deleteEntry(int element, int bucketIndex);

    std::vector<int> hashTable;

    saveBucket cheatSheet;

};

#endif //BIOINF_TABLE_H
