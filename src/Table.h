#ifndef BIOINF_TABLE_H
#define BIOINF_TABLE_H

#include <vector>

class Table {
public:
    explicit Table(uint m);

    ~Table();

    int getElementFromTable(uint bucket, uint element);

    void setElementToTable(uint bucket, uint element, int value);

    std::vector<std::vector<int>> &getHashTable();

    std::vector<int> &getBucket(int bucketNum);

    void printTableToScreen();

    std::vector<std::vector<int>> hashTable;
};

#endif //BIOINF_TABLE_H
