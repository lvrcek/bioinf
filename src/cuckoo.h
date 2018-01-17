//
// Created by lmartinez on 13.01.2018..
//

#ifndef BIOINF_CUCKOO_H
#define BIOINF_CUCKOO_H


#include <algorithm>
#include <cstring>
#include "constants.h"
#include "vector_table.h"

const int maxNumKicks = 500;


/*
 *  Implementation of class used as a cuckoo filter.
 *  Hash table in which elements are stored is of type TableNew,
 *  which is a class imeplemented in vector_table.h.
 */

class CuckooFilterNew {

    std::vector<std::vector<std::bitset<F>>> vector;
    TableNew table = TableNew(nullptr);

    //std::bitset<F> fp_storage;
    //std::bitset<F> temp_fp_storage;

    std::hash<std::bitset<F>> hash_fn;
    std::hash<std::string> hash_str;

public:

    /*
     *  Constructor for class CuckooFilterNew. Takes no arguments
     *  and resizes vector to values specified in cosntants.h, where
     *  M represents number of buckets in a table and B represents
     *  number of slots per bucket. 
     */   

    explicit CuckooFilterNew() {
        vector.resize(M);
        for (int i = M; i--;) {
            vector[i].reserve(B);
        }
        table = TableNew(&vector);
    }


    /*
     *  Destructor for class CuckooFilterNew.
     *  Deletes table and vector elements from the memory.
     */

    ~CuckooFilterNew() {
        delete (&table);
        delete (&vector);
    }


    //size_t HashFunction(const std::string &word);

    std::bitset<F> Fingerprint(const std::string &word);

    bool InsertEntry(const std::string &word);

    bool LookupEntry(const std::string &word);

    bool DeleteEntry(const std::string &word);
};


/*
 *  A hash function which takes string as argument and returns
 *  element of type size_t, which represents in which bucket
 *  fingerprint of element should be stored.
 */
/*
size_t CuckooFilterNew::HashFunction(const std::string &word) {
	unsigned long hash = 0xcbf29ce484222325;
	char *cstr = new char[word.length() + 1];
	strcpy(cstr, word.c_str());
	for(char *c = cstr; (*c)!=0; c++) {
		hash = hash ^ *c;
		hash = hash * 1099511628211;
	}
	delete[] cstr;
	return hash % M;
}
*/
/*
size_t CuckooFilterNew::HashFunction(const std::string &word) {
    int seed = 31;
    unsigned long hash = 1;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i] * word[i];
    return hash % M;
}
*/
/*
size_t CuckooFilterNew::HashFunction(const std::bitset fingerprint) {
    int seed = 31;
    unsigned long hash = 1;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i] * word[i];
    return hash % M;
}*/


/*
 *  A hash function which takes string as argument and returns
 *  a bitset of F bits which represents a fingerprint of the
 *  given string. Size of fingerprint F is specified in constants.h
 */

std::bitset<F> CuckooFilterNew::Fingerprint(const std::string &word) {
    int seed = 19;
    unsigned long hash = 1;
    for (int i = 0; i<word.length(); i++)
        hash = (hash * seed) + word[i];
    std::bitset<F> f(hash);
    return f;
}


/*
 *  A function which takes one argument of type string. First it finds fingerprint
 *  of the given argument. Then it finds two possible buckets where fingerprint
 *  of the element could be stored and checks if either has empty slot.
 *  If at least one has empty slot, it stores fingerprint in that slot and returns true.
 *  Otherwise, it randomly chooses an element already stored in either bucket
 *  and stores fingerprint in its place. Kicked out element is then placed in his
 *  other possible bucket. If that one is full as well, process of replacing continues
 *  until maximum number of kicks has been achieved, which means that
 *  table is (at least almost) full.
 */

bool CuckooFilterNew::InsertEntry(const std::string &word) {
    std::bitset<F> fp_storage = Fingerprint(word);
    //size_t i1 = HashFunction(word);
    size_t i1 = (hash_str(word) % M);
    size_t i2 = i1 ^ (hash_fn(fp_storage) % M);
    if (table.GetBucketSize(i1) < B) {
        table.AddElementToBucket(i1, &fp_storage);
        return true;
    } else if (table.GetBucketSize(i2) < B) {
        table.AddElementToBucket(i2, &fp_storage);
        return true;
    }
    int random = std::rand() % 2;
    size_t i = random == 0 ? i1 : i2;
    for (int n = 0; n < maxNumKicks; n++) {
        random = std::rand() % table.GetBucketSize(i);
        std::bitset<F> temp_fp_storage = table.GetElementFromTable(i, random);
        table.SetElementToTable(i, random, &fp_storage);
        fp_storage = temp_fp_storage;
        i = i ^ (hash_fn(fp_storage) % M);
        if (table.GetBucketSize(i) < B) {
            table.AddElementToBucket(i, &fp_storage);
            return true;
        }
    }
    std::cout << "Failed to insert element: " << word << std::endl;
    return false;
}


/*
 *  A fucntion which takes one argument of type string, finds buckets
 *  in which it could be stored and checks if fingerprint of the argument
 *  is stored in either bucket. Returns true if it is, false otherwise.
 */

bool CuckooFilterNew::LookupEntry(const std::string &word) {
    std::bitset<F> fp_storage = Fingerprint(word);
    //size_t i1 = HashFunction(word);
    size_t i1 = (hash_str(word) % M);
    size_t i2 = i1 ^ (hash_fn(fp_storage) % M);
    return table.ContainsElement(i1, i2, &fp_storage);
}


/*
 *  A fucntion which takes one argument of type string, finds buckets
 *  in which it could be stored and checks if fingerprint of the argument
 *  is stored in either bucket and deletes it. Returns true if fingerprint
 *  is found and deleted, false otherwise.
 */

bool CuckooFilterNew::DeleteEntry(const std::string &word) {
    std::bitset<F> fp_storage = Fingerprint(word);
    //size_t i1 = HashFunction(word);
    size_t i1 = (hash_str(word) % M);
    size_t i2 = i1 ^ (hash_fn(fp_storage) % M);
    if (table.ContainsElement(i1, &fp_storage)) {
        table.DeleteElementFromBucket(i1, &fp_storage);
        return true;
    }
    if (table.ContainsElement(i2, &fp_storage)) {
        table.DeleteElementFromBucket(i1, &fp_storage);

        return true;
    }

    return false;
}


#endif //BIOINF_CUCKOO_H
