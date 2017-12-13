#include <iostream>
#include <string>
#include <stdlib.h>
#include <bitset>
#include <sstream>
#include <vector>
#include <set>
#include <time.h>
#include <algorithm>

using namespace std;


#define M 200       //velicina tablice
#define B 4         //broj pretinaca po elementu tablice
#define N 100       //broj elemenata
#define F 8         //broj bitova u fingerprintu


const int MaxNumKicks = 150;

vector< vector<int> > table(M, vector<int>());

int hashFunction(string word) {
    int seed = 877;
    unsigned long hash = 0;
    for(int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i];
    return hash % M;
}

int fingerprint(string word) {
    int seed = 293;
    unsigned long hash = 0;
    for(int i = 0; i < word.length(); i++)
        hash = (hash * seed) + word[i];
    bitset<F> f(hash % 149);
    return (int) f.to_ulong();
}

bool Insert(string word) {
    int f = fingerprint(word);
    int i1 = hashFunction(word);
    ostringstream convert;
    convert << f;
    int i2 = i1 ^ hashFunction(convert.str());
    if(table[i1].size() < B) {
        table[i1].push_back(f);
        return true;
    }
    else if(table[12].size()< B) {
        table[i2].push_back(f);
        return true;
    }
    srand((unsigned) time(NULL));
    int random = rand() % 2;
    int i;
    i = random == 0 ? i1 : i2;
    for(int n=0; n<MaxNumKicks; i++) {
        random = rand() % 4;
        int temp = table[i][random];
        table[i][random] = f;
        f = temp;
        convert << f;
        i = i ^ hashFunction(convert.str());
        if(table[i].size() < B) {
            table[i].push_back(f);
            return true;
        }
    }
    return false;
}

bool Lookup(string word) {
    int f = fingerprint(word);
    int i1 = hashFunction(word);
    ostringstream convert;
    convert << f;
    int i2 = i1 ^ hashFunction(convert.str());
    if( find(table[i1].begin(), table[i1].end(), f) != table[i1].end())
        return true;
    if( find(table[i2].begin(), table[i2].end(), f) != table[i2].end())
        return true;
    return false;
}

bool Delete(string word) {
    int f = fingerprint(word);
    int i1 = hashFunction(word);
    ostringstream convert;
    convert << f;
    int i2 = i1 ^ hashFunction(convert.str());
    vector<int>::iterator it = find(table[i1].begin(), table[i1].end(), f);
    if( it != table[i1].end()) {
        table[i1].erase(it);
        return true;
    }
    it = find(table[i2].begin(), table[i2].end(), f);
    if( it != table[i2].end()) {
        table[i2].erase(it);
        return true;
    }
    return false;
}


int main() {
    return 0;
}
