#ifndef BIOINF_CUCKOOFILTER_H
#define BIOINF_CUCKOOFILTER_H

#include <string>
#include "Table.h"

#define M 15      //number of buckets in a table
#define B 8       //number of elements in a single bucket
#define N 100     //total number of elements to be inserted in a bucket
#define F 8       //size of fingerprint in bits
static int MaxNumKicks = 150;

int hashFunction(std::string word);

int fingerprint(std::string word);

bool insertEntry(Table &table, std::string word);

bool lookupEntry(Table &table, std::string word);

bool deleteEntry(Table &table, std::string word);

#endif //BIOINF_CUCKOOFILTER_H
