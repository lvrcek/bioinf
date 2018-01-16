//
// Created by lmartinez on 13.01.2018..
//

#ifndef BIOINF_VECTORTABLE_H
#define BIOINF_VECTORTABLE_H

#include "constants.h"
#include <vector>
#include <bitset>
#include <algorithm>

/*
 *  Implementation of class used as a table in cuckoo filter.
 *  It is a hash table implemented as vector of bitset vector,
 *  where total size of a table is M and every vector in table 
 *  contains B bitset elements.
 */

class TableNew {

    std::vector<std::vector<std::bitset<F>>> *hash_table;

public:

    /*
     *  Constructor for TableNew class. It takes one argument of type vector
     *  which contains vectors of bitsets, and is used as starting point for
     *  hash table.
     */

    explicit TableNew(std::vector<std::vector<std::bitset<F> >> *vector) {
        this->hash_table = vector;
    }

    std::bitset<F> GetElementFromTable(size_t bucket_index, size_t element_index);

    void SetElementToTable(size_t bucket_index, size_t element_index, std::bitset<F> element);

    void AddElementToBucket(size_t bucket_index, std::bitset<F> element);

    void DeleteElementFromBucket(size_t bucket_index, std::bitset<F> element);

    size_t GetBucketSize(size_t bucket_index);

    std::vector<std::bitset<F>> *GetBucket(size_t bucket_index);

    bool ContainsElement(size_t bucket_index_1, size_t bucket_index_2, std::bitset<F> element);

    bool ContainsElement(size_t bucket_index, std::bitset<F> element);

};


/*
 *  A function which takes two arguments: index of a bucket and 
 *  index of element in that bucket. It returns a fingerprint of type bitset
 *  stored at the given position in the table.
 */

std::bitset<F> TableNew::GetElementFromTable(size_t bucket_index, size_t element_index) {
    return (*hash_table)[bucket_index][element_index];
}


/*
 *  A function which takes three arguments: index of bucket, index of
 *  an element in that bucket and a fingerprint. It stores the given
 *  fingerprint at the given position in the table.
 */

void TableNew::SetElementToTable(size_t bucket_index, size_t element_index, std::bitset<F> element) {
    (*hash_table)[bucket_index][element_index] = element;
}


/*
 *  A function which takes two arguments: index of bucket and element to be stored
 *  in that bucket. Function then pushes the given element to the back of the given bucket. 
 */

void TableNew::AddElementToBucket(size_t bucket_index, std::bitset<F> element) {
    (*hash_table)[bucket_index].push_back(element);
}


/*
 *  A function which takes two arguments: index of a bucket and element to be removed.
 *  Function then removes the given element from the specified bucket.
 */

void TableNew::DeleteElementFromBucket(size_t bucket_index, std::bitset<F> element) {
    std::vector<std::bitset<F>> vec = (*hash_table)[bucket_index];
    vec.erase(std::remove(vec.begin(), vec.end(), element), vec.end());
}


/*
 *  A function which takes one argument: index of a bucket. It then returns
 *  size of the given bucket.
 */

size_t TableNew::GetBucketSize(size_t bucket_index) {
    return (*hash_table)[bucket_index].size();
}


/*
 *  A function which takes one argument: index of a bucket. It then returns
 *  the whole bucket at the given index.
 */

std::vector<std::bitset<F>> *TableNew::GetBucket(size_t bucket_index) {
    return &((*hash_table)[bucket_index]);
}


/*
 *  A function which takes three elements: bucket indexes 1 and 2 and a fingerprint.
 *  It then checks if given fingerprint is located in either bucket. If so, it
 *  returns true. Otherwise, it returns false.
 */

bool TableNew::ContainsElement(size_t bucket_index_1, size_t bucket_index_2, std::bitset<F> element) {
    if (std::find((*GetBucket(bucket_index_1)).begin(), (*GetBucket(bucket_index_1)).end(), element) !=
        (*GetBucket(bucket_index_1)).end())
        return true;
    if (std::find((*GetBucket(bucket_index_2)).begin(), (*GetBucket(bucket_index_2)).end(), element) !=
        (*GetBucket(bucket_index_2)).end())
        return true;
    return false;
}


/*
 *  A function which takes two arguments: bucket index and a fingerprint.
 *  It then checks if fingerprint is located in the given bucket. If so,
 *  it returns true, otherwise it returns false.
 */

bool TableNew::ContainsElement(size_t bucket_index, std::bitset<F> element) {
    return std::find((*GetBucket(bucket_index)).begin(),
                     (*GetBucket(bucket_index)).end(),
                     element) != (*GetBucket(bucket_index)).end();
}


#endif //BIOINF_VECTORTABLE_H