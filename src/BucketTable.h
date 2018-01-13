#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>


class saveBucket{
    std::vector<std::vector<int> > table;
    std::set< std::vector<int> > global;

void findOneCombination(std::vector<int> series, int r, int howFarInSeries, std::vector<int> tmp);
public:
    saveBucket(int bucketSize, int fingerprintSize);
    saveBucket();
    void print();
    std::vector<int> get(int index);
    int findVector(std::vector<int> target);
    int lookupEntry(int index,int fingerprint);
    int insertEntry(int index,int fingerprint);
    int deleteEntry(int index,int fingerprint);
    int countZeroes(int index);
    int changeEntry(int index,int fingerprint, int value);
    void printBucket(int index);

};
