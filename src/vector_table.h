//
// Created by lmartinez on 13.01.2018..
//

#ifndef BIOINF_VECTORTABLE_H
#define BIOINF_VECTORTABLE_H

#include "constants.h"
#include <vector>
#include <bitset>
#include <algorithm>

class TableNew {

    std::vector<std::vector<std::bitset<F> >> *hash_table;

public:
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

std::bitset<F> TableNew::GetElementFromTable(size_t bucket_index, size_t element_index) {
    return (*hash_table)[bucket_index][element_index];
}

void TableNew::SetElementToTable(size_t bucket_index, size_t element_index, std::bitset<F> element) {
    (*hash_table)[bucket_index][element_index] = element;
}

void TableNew::AddElementToBucket(size_t bucket_index, std::bitset<F> element) {
    (*hash_table)[bucket_index].push_back(element);
}

void TableNew::DeleteElementFromBucket(size_t bucket_index, std::bitset<F> element) {
    std::vector<std::bitset<F>> vec = (*hash_table)[bucket_index];
    vec.erase(std::remove(vec.begin(), vec.end(), element), vec.end());
}

size_t TableNew::GetBucketSize(size_t bucket_index) {
    return (*hash_table)[bucket_index].size();
}

std::vector<std::bitset<F>> *TableNew::GetBucket(size_t bucket_index) {
    return &((*hash_table)[bucket_index]);
}

bool TableNew::ContainsElement(size_t bucket_index_1, size_t bucket_index_2, std::bitset<F> element) {
    if (std::find((*GetBucket(bucket_index_1)).begin(), (*GetBucket(bucket_index_1)).end(), element) !=
        (*GetBucket(bucket_index_1)).end())
        return true;
    if (std::find((*GetBucket(bucket_index_2)).begin(), (*GetBucket(bucket_index_2)).end(), element) !=
        (*GetBucket(bucket_index_2)).end())
        return true;
    return false;
}

bool TableNew::ContainsElement(size_t bucket_index, std::bitset<F> element) {
    return std::find((*GetBucket(bucket_index)).begin(),
                     (*GetBucket(bucket_index)).end(),
                     element) != (*GetBucket(bucket_index)).end();
}


#endif //BIOINF_VECTORTABLE_H
