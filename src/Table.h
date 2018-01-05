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
    explicit Table(unsigned int m);

    ~Table();

    std::bitset<F> getElementFromTable(unsigned int bucket, unsigned int element);

    void setElementToTable(unsigned int bucket, unsigned int element, std::bitset<F> value);

    std::vector<std::vector<std::bitset<F> > > &getHashTable();

    std::vector<std::bitset<F> > &getBucket(int bucketNum);

    void printTableToScreen();

    std::vector<std::vector<std::bitset<F> > > hashTable;
};

#endif //BIOINF_TABLE_H
