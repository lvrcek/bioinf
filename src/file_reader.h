//
// Created by lmartinez on 03.01.2018..
//


#ifndef BIOINF_FILEREADER_H
#define BIOINF_FILEREADER_H

#include <fstream>
#include <iostream>
#include "cuckoo.h"


/*
 *  A class used for reading genome of E. coli from a file Ecoli.fa.
 */

class FileReader {

    std::string file_name = "src/resources/Ecoli.fa";

public:

    explicit FileReader(std::string file) {
        file_name = file;
    }

    bool ReadSimpleCuckooTable(size_t k, int num_entries, CuckooFilterNew *filter);
};


/*
 *  A function which takes three arguments: size of k-meres which will be read,
 *  number of k-meres which will be read and pointer to cuckoo filter.
 *  First, this function reads the content of a give file specified in file_name
 *  and stores it in the variable content. Afterwards, it inserts k-meres from
 *  variable content to the cuckoo filter and then it checks if all k-meres can be
 *  found in the filter.  Returns true if all inserted k-meres are found, and false
 *  if otherwise.
 */

bool FileReader::ReadSimpleCuckooTable(size_t k, int num_entries, CuckooFilterNew *filter) {
    std::ifstream input(file_name);
    if (!input.good()) {
        std::cout << "Error opening '" << file_name << "'." << std::endl;
        return false;
    }

    std::string line, name, content;

    std::getline(input, line);
    if (line[0] != '>') {
        std::cout << "Invalid file format!!" << std::endl;
        return false;
    }

    while (std::getline(input, line).good()) {
        if (line[0] == '>') continue;
        //std::cout << line <<std::endl;
        content += line;
        if (content.length() > num_entries + k - 1) break;
    }

    if (content.length() - k + 1 < num_entries) {
        std::cout << "Not enough entries in first sequence! Returning empty table." << std::endl;
        return false;
    }

    bool success;
    for (size_t i = num_entries; i--;) {
        std::string entry = content.substr(i, k);
        success = filter->InsertEntry(entry);
        if (!success) {
            std::cout << "Error while inserting entry number " << i << " to table. Returning current table."
                      << std::endl;
            return false;
        }
    }

    std::cout << "All entries successfully added to table." << std::endl;

    for (size_t i = num_entries; i--;) {
        std::string entry = content.substr(i, k);
        success = filter->LookupEntry(entry);
        if (!success) {
            std::cout << "Error while looking up entry " << i << ". Element " << entry << " not found." << std::endl;
            return false;
        }
    }

    std::cout << "All entries successfully found in table." << std::endl;
    return true;
}

#endif //BIOINF_FILEREADER_H
