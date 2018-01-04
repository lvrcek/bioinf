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

int hashFunction(std::string word) {
    int seed = 31;
    unsigned long hash = 1;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i]*word[i];
    return hash % M;
}

/*
 * A hash function which taks word (string) as an argument
 * and returns its fingerprint as integer
 */


//is returning int right?
int fingerprint(std::string word) {
    int seed = 53; 
    unsigned long hash = 0;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i]*word[i];
    std::bitset<F> f(hash);
    return (int) f.to_ulong();
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
    int f = fingerprint(word);
    int i1 = hashFunction(word);
	//table.printTableToScreen(); // print table
    std::ostringstream convert;
    convert << f;
    int i2 = (i1 ^hashFunction(convert.str())) % M;
    if (table.getHashTable()[i1].size() < B) {
        table.getHashTable()[i1].push_back(f);
        return true;
    } else if (table.getHashTable()[i2].size() < B) {
        table.getHashTable()[i2].push_back(f);
        return true;
    }
    srand((unsigned) time(NULL));
    int random = rand() % 2;
    int i;
    i = random == 0 ? i1 : i2;
    for (int n = 0; n < MaxNumKicks; n++) {
        random = rand() % B;    //should randomly select entry from bucket (this would not work)
        int temp = table.getHashTable()[i][random];
        table.getHashTable()[i][random] = f;
        f = temp;
	convert.str(std::string()); // clean string stream
        convert << f;
        i = (i ^ hashFunction(convert.str())) % M;
        if (table.getHashTable()[i].size() < B) {
            table.getHashTable()[i].push_back(f);
            return true;
        }
    }
	std::cout<<"tablica je puna"<<std::endl;
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
    int f = fingerprint(word);
    int i1 = hashFunction(word);
    std::ostringstream convert;
    convert << f;
    int i2 = i1 ^hashFunction(convert.str());
    if (std::find(table.getHashTable()[i1].begin(), table.getHashTable()[i1].end(), f) !=
        table.getHashTable()[i1].end())
        return true;
    if (std::find(table.getHashTable()[i2].begin(), table.getHashTable()[i2].end(), f) !=
        table.getHashTable()[i2].end())
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
    int f = fingerprint(word);
    int i1 = hashFunction(word);
    std::ostringstream convert;
    convert << f;
    int i2 = i1 ^hashFunction(convert.str());
    std::vector<int>::iterator it =
		std::find(table.getHashTable()[i1].begin(), table.getHashTable()[i1].end(), f);
    if (it != table.getHashTable()[i1].end()) {
        table.getHashTable()[i1].erase(it);
        return true;
    }
    it = std::find(table.getHashTable()[i2].begin(), table.getHashTable()[i2].end(), f);
    if (it != table.getHashTable()[i2].end()) {
        table.getHashTable()[i2].erase(it);
        return true;
    }
    return false;
}
