//
// Created by lmartinez on 03.01.2018..
//

#ifndef BIOINF_FILEREADER_H
#define BIOINF_FILEREADER_H

#include "table.h"

Table *ReadSimpleCuckooTable(int k, int num_entries);

Table *ReadWholeSequence(int k);

#endif //BIOINF_FILEREADER_H
