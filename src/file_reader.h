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

    std::string file_name = "C:\\Users\\lmartinez\\Projects\\FER\\bioinf\\src\\resources\\Ecoli.fa";
    std::string fp_file_name = "";

public:

    explicit FileReader(std::string file, std::string fpfile) {
        file_name = file;
        fp_file_name = fpfile;
    }

    bool ReadSimpleCuckooTable(int k, int num_entries, CuckooFilterNew *filter);
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

    std::ifstream inputFP(fp_file_name);
    if (!inputFP.good()) {
        std::cout << "Error opening '" << fp_file_name << "'." << std::endl;
        return false;
    }

    int false_positives = 0;
    int total = 0;
    while (std::getline(inputFP, line).good()) {
        if (line[0] == '>') continue;
        //std::cout << line <<std::endl;
        success = filter->LookupEntry(line);
        if (success) {
            false_positives++;
        }
        total++;
    }

    std::cout << "false positive rate is " << 100.0 * false_positives / total << "%\n";
    return true;
}

#endif //BIOINF_FILEREADER_H
