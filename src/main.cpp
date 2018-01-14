#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <chrono>
#include "Table.cpp"
#include "CuckooFilter.cpp"

namespace patch {
    template<typename T>
    std::string to_string(const T &m) {
        std::ostringstream stm;
        stm << m;
        return stm.str();
    }
}

using namespace std;

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    auto *table = new Table();

    int totalItems = 10000;

    for (int i = 0; i < totalItems; i++) {

        if (!insertEntry(*table, patch::to_string(i))) {
            std::cout << "Error while inserting elements!!" << i << std::endl;
            return 1;
        }
    }


    std::cout << "Inserted all 40 000 elements!" << std::endl;

    for (int i = 0; i < totalItems; i++) {
        bool result = lookupEntry(*table, patch::to_string(i));
        if (!result) {
            std::cout << "Element" << i << "not found!" << std::endl;
            return 1;
        }
    }

    std::cout << "Asserted all 1 000 000 elements!" << std::endl;

    int total_queries = 0;
    int false_queries = 0;
    for (int i = totalItems; i < 2 * totalItems; i++) {
        if (lookupEntry(*table, patch::to_string(i))) {
            false_queries++;
        }
        total_queries++;
    }

    // Output the measured false positive rate
    std::cout << "false positive rate is " << 100.0 * false_queries / total_queries << "%\n";

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "Elapsed time is " << elapsed.count() << std::endl;

   // free(table);
    return 0;
}
