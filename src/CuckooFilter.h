#ifndef BIOINF_CUCKOOFILTER_H
#define BIOINF_CUCKOOFILTER_H

#include <string>
#include "Table.h"

#define M 15       //velicina tablice
#define B 8       //broj pretinaca po elementu tablice
#define N 100       //broj elemenata
#define F 8         //broj bitova u fingerprintu
static int MaxNumKicks = 150;

int hashFunction(std::string word);

int fingerprint(std::string word);

bool insertEntry(Table &table, std::string word);

bool lookupEntry(Table &table, std::string word);

bool deleteEntry(Table &table, std::string word);

#endif //BIOINF_CUCKOOFILTER_H
