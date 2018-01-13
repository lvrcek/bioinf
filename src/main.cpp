#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <chrono>
#include "cuckoo.h"
#include "file_reader.h"

namespace patch {
    template<typename T>
    std::string to_string(const T &m) {
        std::ostringstream stm;
        stm << m;
        return stm.str();
    }
}

using namespace std;

int main(int argc, char *argv[]) {

    //  CuckooFilterNew *fileCuckoo = new CuckooFilterNew();
    //std::string fileName = "C:\\Users\\lmartinez\\Projects\\FER\\bioinf\\src\\resources\\Ecoli.fa";
    //FileReader *reader = new FileReader(fileName);

    //  reader->readSimpleCuckooTable(20,1000000,fileCuckoo);
    //  reader->assertSimpleCuckooTable(20,1000000,fileCuckoo);

    auto start = std::chrono::high_resolution_clock::now();

    CuckooFilterNew *cuckoo = new CuckooFilterNew();
    size_t totalItems = 33554432 * 4;

    auto startInsert = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < totalItems; i++) {
        if (!cuckoo->insertEntry(std::to_string(i))) {
            std::cout << "Error while inserting elements!!" << i << std::endl;
            return 1;
        }
    }

    auto finishInsert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedInsert = finishInsert - startInsert;
    std::cout << "Insertion time is: " << elapsedInsert.count() << std::endl;


    auto startLookup = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < totalItems; i++) {
        if (!cuckoo->lookupEntry(std::to_string(i))) {
            std::cout << "Error while looking up elements!!" << i << std::endl;
            return 1;
        }
    }

    auto finishLookup = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedLookup = finishLookup - startLookup;
    std::cout << "Lookup time is: " << elapsedLookup.count() << std::endl;


    int total_queries = 0;
    int false_queries = 0;
    for (int i = totalItems; i < 2 * totalItems; i++) {
        if (cuckoo->lookupEntry(std::to_string(i))) {
            false_queries++;
        }
        total_queries++;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Execution time is: " << elapsed.count() << std::endl;
    std::cout << "false positive rate is " << 100.0 * false_queries / total_queries << "%\n";

    free(cuckoo);
}
/*
int oldmain() {

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<std::bitset<F>>> vector;
    vector.resize(M);
    for(int i = 0; i<M; i++){
        vector.reserve(B);
    }
    auto *table = new Table(&vector);

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;

    std::string *entries = new std::string[1000000];
    for(int i = 0; i<1000000; i++){
        entries[i] = std::to_string(i);
    }

    std::cout << "Init time is " << elapsed.count() << std::endl;
    int totalItems = 1000000;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < totalItems; i++) {
        if (!insertEntry(table, std::to_string(i))) {
            std::cout << "Error while inserting elements!!" << i << std::endl;
            return 1;
        }
    }

    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish-start;
  //  std::cout << "Insertion time is " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < totalItems; i++) {
        bool result = lookupEntry(table, std::to_string(i));
        if (!result) {
            std::cout << "Element" << i << "not found!" << std::endl;
            return 1;
        }
    }

    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish-start;
 //   std::cout << "Assertion time is " << elapsed.count() <<std::endl;

    int total_queries = 0;
    int false_queries = 0;
    for (int i = totalItems; i < 2 * totalItems; i++) {
        if (lookupEntry(table, std::to_string(i))) {
            false_queries++;
        }
        total_queries++;
    }

    // Output the measured false positive rate
    std::cout << "false positive rate is " << 100.0 * false_queries / total_queries << "%\n";


    free(table);
    return 0;
}

 */

