#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include "Table.h"
#include "CuckooFilter.h"
#include "FileReader.h"
#include <assert.h>

namespace patch
{
    template < typename T > std::string to_string( const T& m )
    {
        std::ostringstream stm ;
        stm << m ;
        return stm.str() ;
    }
}

using namespace std;

int main() {

    Table *table2 = readSimpleCuckooTable(3, 100);
    table2->printTableToScreen();

    return 0;
}

int oldMain() {
    auto *table = new Table(M);

    cout << "Should print empty table\n";
    table->printTableToScreen();

    cout << "Add one entry\n";
    insertEntry(*table, "A");
    table->printTableToScreen();

    cout << "Add A 3 more times\n";
    insertEntry(*table, "A");
    insertEntry(*table, "A");
    insertEntry(*table, "A");
    table->printTableToScreen();

    cout << "Add 4th A - should go to another bucket\n";
    insertEntry(*table, "A");
    table->printTableToScreen();

    cout << "Remove A - should remove from original bucket\n";
    deleteEntry(*table, "A");
    table->printTableToScreen();

    cout << "Looking up A : " << lookupEntry(*table, "A") << "\n";

    cout << "Should remove all A entries\n";
    deleteEntry(*table, "A");
    deleteEntry(*table, "A");
    deleteEntry(*table, "A");
    deleteEntry(*table, "A");
    cout << "Looking up A : " << lookupEntry(*table, "A") << "\n";
    table->printTableToScreen();

    for (size_t i = 0; i < 100; i++) {
        if (!insertEntry(*table, std::to_string(i))) {
            break;
        }
    }

    table->printTableToScreen();

    for (size_t i = 0; i < 100; i++) {
        assert(lookupEntry(*table, std::to_string(i)));
    }

    delete (table);
    return 0;
}