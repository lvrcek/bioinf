#ifndef BIOINF_TABLE_H
#define BIOINF_TABLE_H

#include <vector>

/*
 * Declaration of class Table which represents
 * a cuckoo table in which fingerprints are stored.
 */

class Table {
public:
    explicit Table(unsigned int m);

    ~Table();

    int getElementFromTable(unsigned int bucket, unsigned int element);

    void setElementToTable(unsigned int bucket, unsigned int element, int value);

    std::vector<std::vector<int> > &getHashTable();

    std::vector<int> &getBucket(int bucketNum);

    void printTableToScreen();

    std::vector<std::vector<int> > hashTable;
};

#endif //BIOINF_TABLE_H
