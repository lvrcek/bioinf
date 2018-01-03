#include <iostream>
#include <fstream>
#include "FileReader.h"
#include "CuckooFilter.h"

//TODO problem with clion, need to set it to work on unix
std::string fileName = "C:\\Users\\lmartinez\\Projects\\FER\\bioinf\\src\\resources\\Ecoli.fa";

Table *readSimpleCuckooTable(int k, int numEntries) {

    std::ifstream input(fileName);
    if (!input.good()) {
        std::cout << "Error opening '" << fileName << "'." << std::endl;
        return new Table(0);
    }

    std::string line, name, content;

    std::getline(input, line);
    if (line[0] != '>') {
        std::cout << "Invalid file format!!" << std::endl;
        return new Table(0);
    }

    while (std::getline(input, line).good()) {
        if (line[0] == '>') break;
        //std::cout << line <<std::endl;
        content += line;
        if (content.length() > numEntries + k - 1) break;
    }

    //std::cerr << content.length() << std::endl;

    if (content.length() - k + 1 < numEntries) {
        std::cout << "Not enough entries in first sequence! Returning empty table." << std::endl;
        return new Table(0);
    }

    auto *table = new Table(M);
    bool success;
    for (int i = 0; i < numEntries; i++) {
        std::string entry = content.substr(i, k);
        success = insertEntry(*table, entry);
        if (!success) {
            std::cout << "Error while inserting to table. Returning current table." << std::endl;
            return table;
        } else {
            std::cout << "Added entry: " << entry << std::endl;
        }
    }

    std::cout << "All entries successfully added to table." << std::endl;
    return table;
}

Table *readWholeSequence(int k) {

    std::ifstream input(fileName);
    if (!input.good()) {
        std::cout << "Error opening '" << fileName << "'." << std::endl;
        return new Table(0);
    }

    std::string line, name, content;

    std::getline(input, line);
    if (line[0] != '>') {
        std::cout << "Invalid file format!!" << std::endl;
        return new Table(0);
    }

    while (std::getline(input, line).good()) {
        if (line[0] == '>') break;
        //std::cout << line <<std::endl;
        content += line;
    }

    std::cout << "M = " << M << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "Theoretical maximum number of entries = " << M * B << std::endl;
    std::cout << "Num. of entries for entire sequence = " << content.length() - k + 1 << std::endl;

    if (M * B < content.length() - k + 1) {
        std::cout << "Number of entries would be greater then max table capacity. Returning empty table" << std::endl;
        return new Table(0);
    }

    auto *table = new Table(M);
    bool success;
    int entriesAdded = 0;
    for (int i = 0; i < (content.length() - k + 1); i++) {
        std::string entry = content.substr(i, k);
        success = insertEntry(*table, entry);
        if (!success) {
            std::cout << "Error while inserting to table. Returning current table." << std::endl;
            std::cout << "Successfully inserted " << entriesAdded << " entries." << std::endl;
            return table;
        } else {
            entriesAdded++;
        }
    }

    std::cout << "All entries successfully added to table." << std::endl;
    return table;
}
