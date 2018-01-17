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

    int GetElementFromTable(unsigned int bucket_index, unsigned int element_index);

    void SetElementToTable(unsigned int bucket, unsigned int element, int value);

    std::vector<int> &GetHashTable();

    std::vector<int> GetBucket(int bucket_num);

    size_t GetBucketSize(int bucket_num);

    void AddElementToBucket(int element, int bucket_num);

    void PrintTableToScreen();

    int LookUpEntry(int element, int bucket_index);

    void DeleteEntry(int element, int bucket_index);

    std::vector<int> hash_table;

    SaveBucket cheat_sheet;

};

#endif //BIOINF_TABLE_H
