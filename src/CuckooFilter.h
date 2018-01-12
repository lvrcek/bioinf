#ifndef BIOINF_CUCKOOFILTER_H
#define BIOINF_CUCKOOFILTER_H

#include <string>
#include <bitset>
#include "Table.h"
#include "Constants.h"


static int MaxNumKicks = 150;

size_t hashFunction(std::string word);

std::bitset<F> fingerprint(std::string word);

bool insertEntry(Table &table, std::string word);

bool lookupEntry(Table &table, std::string word);

bool deleteEntry(Table &table, std::string word);

#endif //BIOINF_CUCKOOFILTER_H
