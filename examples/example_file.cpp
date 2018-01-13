#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <chrono>
#include "../src/file_reader.h"

using namespace std;

int main(int argc, char *argv[]) {

    CuckooFilterNew *cuckoo = new CuckooFilterNew();
    std::string file_name = "C:\\Users\\lmartinez\\Projects\\FER\\bioinf\\src\\resources\\Ecoli.fa";
    FileReader *reader = new FileReader(file_name);

    reader->ReadSimpleCuckooTable(20, 1000000, cuckoo);

    free(cuckoo);
}
