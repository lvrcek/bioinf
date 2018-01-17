#ifndef BIOINF_CUCKOOFILTER_H
#define BIOINF_CUCKOOFILTER_H

#include <string>
#include <bitset>
#include "Table.h"
#include "Constants.h"


static int max_num_kicks = 150;

size_t HashFunction(std::string word);

std::bitset<F> Fingerprint(std::string word);

bool InsertEntry(Table &table, std::string word);

bool LookupEntry(Table &table, std::string word);

bool DeleteEntry(Table &table, std::string word);

#endif //BIOINF_CUCKOOFILTER_H
