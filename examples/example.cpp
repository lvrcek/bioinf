#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <chrono>
#include "../src/file_reader.h"
#include "windows.h"
#include "psapi.h"
using namespace std;

int main(int argc, char *argv[]) {

    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

    auto start = std::chrono::high_resolution_clock::now();

    CuckooFilterNew cuckoo;
    std::cout << "Filter: " << sizeof(cuckoo) << std::endl;

    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMeEnd = pmc.PrivateUsage;

    std::cout << "Physical memory used by me is " << virtualMemUsedByMe << " Bytes." << std::endl;
    std::cout << "Physical memory used by me end is " << virtualMemUsedByMeEnd << " Bytes." << std::endl;
    std::cout << "MEM = " << virtualMemUsedByMeEnd - virtualMemUsedByMe << " Bytes." << std::endl;

    auto start_insert = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NCF; i++) {
        if (!cuckoo.InsertEntry(std::to_string(i))) {
            std::cout << "Error while inserting elements!! Failed on: " << i << std::endl;
            return 1;
        }
    }

    auto finish_insert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_insert = finish_insert - start_insert;
    std::cout << "Insertion time is: " << elapsed_insert.count() << std::endl;

    auto start_lookup = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NCF; i++) {
        if (!cuckoo.LookupEntry(std::to_string(i))) {
            std::cout << "Error while looking up elements!!" << i << std::endl;
            return 1;
        }
    }

    auto finish_lookup = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_lookup = finish_lookup - start_lookup;
    std::cout << "Lookup time is: " << elapsed_lookup.count() << std::endl;

    int total_queries = 0;
    int false_queries = 0;
    int max = NCF * 2;
    for (int i = NCF; i < max; i++) {
        if (cuckoo.LookupEntry(std::to_string(i))) {
            false_queries++;
        }
        total_queries++;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Execution time is: " << elapsed.count() << std::endl;
    std::cout << "False positive rate is " << 100.0 * false_queries / total_queries << "%\n";


    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMeEndFInal = pmc.PrivateUsage;

    std::cout << "Physical memory used by me is " << virtualMemUsedByMe << " Bytes." << std::endl;
    std::cout << "Physical memory used by me end is " << virtualMemUsedByMeEndFInal << " Bytes." << std::endl;
    std::cout << "MEM = " << virtualMemUsedByMeEndFInal - virtualMemUsedByMe << " Bytes." << std::endl;

    //free(cuckoo);
}
