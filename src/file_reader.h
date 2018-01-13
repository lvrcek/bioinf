//
// Created by lmartinez on 03.01.2018..
//


#ifndef BIOINF_FILEREADER_H
#define BIOINF_FILEREADER_H

#include <fstream>
#include <iostream>
#include "cuckoo.h"


class FileReader {

    std::string fileName = "C:\\Users\\lmartinez\\Projects\\FER\\bioinf\\src\\resources\\Ecoli.fa";

public:

    explicit FileReader(std::string file) {
        fileName = file;
    }

    bool readSimpleCuckooTable(int k, int numEntries, CuckooFilterNew *filter);
};

bool FileReader::readSimpleCuckooTable(int k, int numEntries, CuckooFilterNew *filter) {
    std::ifstream input(fileName);
    if (!input.good()) {
        std::cout << "Error opening '" << fileName << "'." << std::endl;
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
        if (content.length() > numEntries + k - 1) break;
    }

    //std::cerr << content.length() << std::endl;

    if (content.length() - k + 1 < numEntries) {
        std::cout << "Not enough entries in first sequence! Returning empty table." << std::endl;
        return false;
    }

    bool success;
    for (int i = 0; i < numEntries; i++) {
        std::string entry = content.substr(i, k);
        success = filter->insertEntry(entry);
        if (!success) {
            std::cout << "Error while inserting entry number " << i << " to table. Returning current table."
                      << std::endl;
            return false;
        }
    }

    std::cout << "All entries successfully added to table." << std::endl;

    for (int i = 0; i < numEntries; i++) {
        std::string entry = content.substr(i, k);
        success = filter->lookupEntry(entry);
        if (!success) {
            std::cout << "Error while looking up entry " << i << ". Element " << entry << " not found." << std::endl;
            return false;
        }
    }

    std::cout << "All entries successfully found in table." << std::endl;
    return true;
}

#endif //BIOINF_FILEREADER_H
