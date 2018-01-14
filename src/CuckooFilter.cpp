#include <iostream>
#include <bitset>
#include <sstream>
#include <set>
#include <algorithm>
#include "CuckooFilter.h"



/*
 * A hash function which takes a word (string)
 * and returns integer value of bucket in which
 * it's fingerprint will be stored
 */
size_t hashFunction(std::string word) {
    int seed = 31; //877
    unsigned long hash = 1;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i] * word[i]; //
    return hash % M;
}

/*
 * A hash function which taks word (string) as an argument
 * and returns its fingerprint as integer
 */


//is returning int right?
std::bitset<F> fingerprint(std::string word) {
    int seed = 53; //293
    unsigned long hash = 0;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i] * word[i];
    std::bitset<F> f(hash);
    return f;
}

/*
 * A function to store element in a table, it takes two arguments: table and word.
 * It finds two possible buckets where fingerprint of the element could be stored
 * and checks if either has empty slot. If at least one has empty slot, it stores
 * fingerprint in that slot and returns true. Otherwise, it randomly chooses an element
 * already stored in either bucket and stores fingerprint in its place. Kicked out
 * element is then placed in his other possible bucket. If that one is full as well,
 * process of replacing continues until maximum number of kicks has been achieved,
 * which means that table is (at least almost) full.
 */

bool insertEntry(Table &table, std::string word) {
    std::bitset<F> f = fingerprint(word);
    size_t i1 = hashFunction(word);
    size_t i2 = i1 ^hashFunction(f.to_string());
    if (table.getBucketSize(i1) < B) {
        table.addElementToBucket(f.to_ulong(), i1);
        return true;
    } else if (table.getBucketSize(i2) < B) {
        table.addElementToBucket(f.to_ulong(), i2);
        return true;
    }
    int random = std::rand() % 2;
    size_t i;
    i = random == 0 ? i1 : i2;
    for (int n = 0; n < MaxNumKicks; n++) {
        random = std::rand() % table.getBucketSize(i);
        std::bitset<F> temp(table.getElementFromTable(i, random));
        table.setElementToTable(i, random, f.to_ulong());
        f = temp;
        i = i ^ hashFunction(f.to_string());
        if (table.getBucketSize(i) < B) {
            table.addElementToBucket(f.to_ulong(), i);
            return true;
        }
    }
    return false;
}

/*
 * Function which takes two arguments: table and word.
 * It checks wether given word's fingerprint is stored in the
 * table, by findings buckets in which it coudl be stored and
 * checking if it'f fingerprint is in either. If there is, it returns
 * true, and false otherwise. This is prone to false positives, in
 * case of having two different elements with same hash and same fingerprint.
 */

bool lookupEntry(Table &table, std::string word) {
    std::bitset<F> f = fingerprint(word);
    size_t i1 = hashFunction(word);
    size_t i2 = i1 ^hashFunction(f.to_string());
    if (std::find(table.getBucket(i1).begin(), table.getBucket(i1).end(), f.to_ulong()) !=
        table.getBucket(i1).end())
        return true;
    if (std::find(table.getBucket(i2).begin(), table.getBucket(i2).end(), f.to_ulong()) !=
        table.getBucket(i2).end())
        return true;
    return false;
}


/*
 * A function which takes two arguments: table and word.
 * Similiar to lookup function, but after finding element in
 * a bucket, it removes that element's fingerprint from that
 * bucket and returns true. If there is no such fingerprint
 * in either bucket, it returns false.
 */

bool deleteEntry(Table &table, std::string word) {
    std::bitset<F> f = fingerprint(word);
    size_t i1 = hashFunction(word);
    std::ostringstream convert;
    convert << f;
    size_t i2 = i1 ^hashFunction(convert.str());
    int index = table.lookUpEntry(i1,f.to_ulong());
    if (index!=-1) {
        table.deleteEntry(f.to_ulong(),i1);
        return true;
    }
    index = table.lookUpEntry(i2, f.to_ulong());
    if (index!=i2) {
        table.deleteEntry(f.to_ulong(),i2);
        return true;
    }
    return false;
}
