//
// Created by lmartinez on 13.01.2018..
//

#ifndef BIOINF_CUCKOO_H
#define BIOINF_CUCKOO_H


#include <algorithm>
#include "constants.h"
#include "vector_table.h"

class CuckooFilterNew {

    std::vector<std::vector<std::bitset<F>>> vector;
    TableNew *table;

    std::bitset<F> fp_storage;
    std::bitset<F> temp_fp_storage;

public:
    explicit CuckooFilterNew() {
        vector.resize(M);
        for (int i = 0; i < M; i++) {
            vector[i].reserve(B);
        }
        table = new TableNew(&vector);
    }

    ~CuckooFilterNew() {
        delete (table);
        delete (&vector);
    }


    size_t HashFunction(const std::string &word);

    std::bitset<F> Fingerprint(const std::string &word);

    bool InsertEntry(const std::string &word);

    bool LookupEntry(const std::string &word);

    bool DeleteEntry(const std::string &word);
};

size_t CuckooFilterNew::HashFunction(const std::string &word) {
    int seed = 31; //877
    unsigned long hash = 1;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i] * word[i]; //
    return hash % M;
}

std::bitset<F> CuckooFilterNew::Fingerprint(const std::string &word) {
    int seed = 19; //877
    unsigned long hash = 1;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i]; //


    std::bitset<F> f(hash);
    return f;
}

bool CuckooFilterNew::InsertEntry(const std::string &word) {
    fp_storage = Fingerprint(word);
    size_t i1 = HashFunction(word);
    size_t i2 = i1 ^HashFunction(fp_storage.to_string());
    if (table->GetBucketSize(i1) < B) {
        table->AddElementToBucket(i1, fp_storage);
        return true;
    } else if (table->GetBucketSize(i2) < B) {
        table->AddElementToBucket(i2, fp_storage);
        return true;
    }
    int random = std::rand() % 2;
    size_t i;
    i = random == 0 ? i1 : i2;
    for (int n = 0; n < 500; n++) {
        random = std::rand() % table->GetBucketSize(i);
        temp_fp_storage = table->GetElementFromTable(i, random);
        table->SetElementToTable(i, random, fp_storage);
        fp_storage = temp_fp_storage;
        i = i ^ HashFunction(fp_storage.to_string());
        if (table->GetBucketSize(i) < B) {
            table->AddElementToBucket(i, fp_storage);
            return true;
        }
    }
    std::cout << "Failed to insert element: " << word << std::endl;
    return false;
}

bool CuckooFilterNew::LookupEntry(const std::string &word) {
    fp_storage = Fingerprint(word);
    size_t i1 = HashFunction(word);
    size_t i2 = i1 ^HashFunction(fp_storage.to_string());
    return table->ContainsElement(i1, i2, fp_storage);
}

bool CuckooFilterNew::DeleteEntry(const std::string &word) {
    fp_storage = Fingerprint(word);
    size_t i1 = HashFunction(word);
    size_t i2 = i1 ^HashFunction(fp_storage.to_string());
    if (table->ContainsElement(i1, fp_storage)) {
        table->DeleteElementFromBucket(i1, fp_storage);
        return true;
    }
    if (table->ContainsElement(i2, fp_storage)) {
        table->DeleteElementFromBucket(i1, fp_storage);

        return true;
    }

    return false;
}


#endif //BIOINF_CUCKOO_H
