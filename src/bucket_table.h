#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>


class SaveBucket{
    std::vector<std::vector<int> > table;
    std::set< std::vector<int> > global;

void FindOneCombination(std::vector<int> series, int r, int how_far_in_series, std::vector<int> tmp);
public:
    SaveBucket(int bucket_size, int fingerprint_size);
    SaveBucket();
    void print();
    std::vector<int> Get(int index);
    int FindVector(std::vector<int> target);
    int LookupEntry(int index,int fingerprint);
    int InsertEntry(int index,int fingerprint);
    int DeleteEntry(int index,int fingerprint);
    int CountZeroes(int index);
    int ChangeEntry(int index,int fingerprint, int value);
    void PrintBucket(int index);

};
