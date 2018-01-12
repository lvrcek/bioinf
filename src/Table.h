#ifndef BIOINF_TABLE_H
#define BIOINF_TABLE_H

#include <vector>
#include <bitset>
#include "Constants.h"

/*
 * Declaration of class Table which represents
 * a cuckoo table in which fingerprints are stored.
 */

class Table {
public:
    explicit Table();

    ~Table();

    std::bitset<F> getElementFromTable(unsigned int bucketIndex, unsigned int elementIndex);

    void setElementToTable(unsigned int bucket, unsigned int element, std::bitset<F> value);

    std::vector<std::vector<std::bitset<F> > > &getHashTable();

    std::vector<std::bitset<F> > &getBucket(int bucketNum);

    size_t getBucketSize(int bucketNum);

    void addElementToBucket(std::bitset<F> element, int bucketNum);

    void printTableToScreen();

    std::vector<std::vector<std::bitset<F> > > hashTable;
};

#endif //BIOINF_TABLE_H
