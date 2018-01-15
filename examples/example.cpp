#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <chrono>
#include "../src/file_reader.h"

using namespace std;

int main(int argc, char *argv[]) {

    auto start = std::chrono::high_resolution_clock::now();

    CuckooFilterNew *cuckoo = new CuckooFilterNew();

    auto start_insert = std::chrono::high_resolution_clock::now();

    for (int i = N; i--;) {
        if (!cuckoo->InsertEntry(std::to_string(i))) {
            std::cout << "Error while inserting elements!! Failed on: " << i << std::endl;
            return 1;
        }
    }

    auto finish_insert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_insert = finish_insert - start_insert;
    std::cout << "Insertion time is: " << elapsed_insert.count() << std::endl;

    auto start_lookup = std::chrono::high_resolution_clock::now();

    for (int i = N; i--;) {
        if (!cuckoo->LookupEntry(std::to_string(i))) {
            std::cout << "Error while looking up elements!!" << i << std::endl;
            return 1;
        }
    }

    auto finish_lookup = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_lookup = finish_lookup - start_lookup;
    std::cout << "Lookup time is: " << elapsed_lookup.count() << std::endl;

    int total_queries = 0;
    int false_queries = 0;
    for (int i = N; i < (N<<1); i++) {
        if (cuckoo->LookupEntry(std::to_string(i))) {
            false_queries++;
        }
        total_queries++;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Execution time is: " << elapsed.count() << std::endl;
    std::cout << "False positive rate is " << 100.0 * false_queries / total_queries << "%\n";

    free(cuckoo);
}
