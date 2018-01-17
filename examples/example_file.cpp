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
    std::string file_name = "C:\\Users\\lmartinez\\Desktop\\sint\\sint11.fa";
    std::string file_namefp = "C:\\Users\\lmartinez\\Desktop\\sint\\100sint11.fa";

    FileReader reader(file_name, file_namefp);
    reader.ReadSimpleCuckooTable(100, 1000000, &cuckoo);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Execution time is: " << elapsed.count() << std::endl;

    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMeEnd = pmc.PrivateUsage;

    std::cout << "Physical memory used by me is " << virtualMemUsedByMe << " Bytes." << std::endl;
    std::cout << "Physical memory used by me end is " << virtualMemUsedByMeEnd << " Bytes." << std::endl;
    std::cout << "MEM = " << virtualMemUsedByMeEnd - virtualMemUsedByMe << " Bytes." << std::endl;



}
