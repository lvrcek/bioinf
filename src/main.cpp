#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include "Table.h"
#include "CuckooFilter.h"

using namespace std;

void methodTest(Table &table, int a) {
    table.setElementToTable(0, 0, a);
    table.getHashTable()[0].push_back(a);
}

int main() {
    std::cout << "Hello Cuckoo!" << std::endl;
    auto *table = new Table(5, 5);
    methodTest(*table, 5);
    //insert expands number of elements?
    insertEntry(*table, "A");
    table->printTableToScreen();
    cout << lookupEntry(*table, "A") << endl;
    deleteEntry(*table, "A");
    table->printTableToScreen();
    cout << lookupEntry(*table, "A") << endl;
    return 0;
}