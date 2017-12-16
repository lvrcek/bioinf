#include <iostream>
#include <bitset>
#include <sstream>
#include <set>
#include <algorithm>
#include "CuckooFilter.h"

int hashFunction(std::string word) {
    int seed = 877;
    unsigned long hash = 0;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i];
    return hash % M;
}

int fingerprint(std::string word) {
    int seed = 293;
    unsigned long hash = 0;
    for (int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i];
    std::bitset<F> f(hash % 149);
    return (int) f.to_ulong();
}

bool insertEntry(Table &table, std::string word) {
    int f = fingerprint(word);
    int i1 = hashFunction(word);
    std::ostringstream convert;
    convert << f;
    int i2 = i1 ^hashFunction(convert.str());
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
    for (int n = 0; n < MaxNumKicks; i++) {
        random = rand() % 4;
        int temp = table.getHashTable()[i][random];
        table.getHashTable()[i][random] = f;
        f = temp;
        convert << f;
        i = i ^ hashFunction(convert.str());
        if (table.getHashTable()[i].size() < B) {
            table.getHashTable()[i].push_back(f);
            return true;
        }
    }
    return false;
}

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


bool deleteEntry(Table &table, std::string word) {
    int f = fingerprint(word);
    int i1 = hashFunction(word);
    std::ostringstream convert;
    convert << f;
    int i2 = i1 ^hashFunction(convert.str());
    std::vector<int>::iterator it = std::find(table.getHashTable()[i1].begin(), table.getHashTable()[i1].end(), f);
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
