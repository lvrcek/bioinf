//
// Created by lmartinez on 03.01.2018..
//

#ifndef BIOINF_FILEREADER_H
#define BIOINF_FILEREADER_H

#include "Table.h"

Table *readSimpleCuckooTable(int k, int numEntries);

Table *readWholeSequence(int k);

#endif //BIOINF_FILEREADER_H
