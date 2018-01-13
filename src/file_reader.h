//
// Created by lmartinez on 03.01.2018..
//


#ifndef BIOINF_FILEREADER_H
#define BIOINF_FILEREADER_H

#include <fstream>
#include <iostream>
#include "cuckoo.h"


class FileReader {

    std::string file_name = "C:\\Users\\lmartinez\\Projects\\FER\\bioinf\\src\\resources\\Ecoli.fa";

public:

    explicit FileReader(std::string file) {
        file_name = file;
    }

    bool ReadSimpleCuckooTable(int k, int num_entries, CuckooFilterNew *filter);
};

bool FileReader::ReadSimpleCuckooTable(int k, int num_entries, CuckooFilterNew *filter) {
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
    for (int i = 0; i < num_entries; i++) {
        std::string entry = content.substr(i, k);
        success = filter->InsertEntry(entry);
        if (!success) {
            std::cout << "Error while inserting entry number " << i << " to table. Returning current table."
                      << std::endl;
            return false;
        }
    }

    std::cout << "All entries successfully added to table." << std::endl;

    for (int i = 0; i < num_entries; i++) {
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
