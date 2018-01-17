#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include "Table.h"


//saveBucket cheat_sheet(4,4);

/*
 * A constructor for class Table. Hash table is declared as vector of m vectors of integers.
 * Each inner vector represents a bucket, meaning it can store at most same number of elements
 * as is number of slots in a bucket (given with a constant B).
 */


Table::Table() : cheat_sheet(B,F) {
    this->hash_table.resize(M);
};

/*
 * A default destructor for class Table.
 */

Table::~Table() = default;

/*
 * A function which takes two arguments: bucket and element.
 *  It returns fingerprint stored at specified bucket and position in bucket (element).
 */

int Table::GetElementFromTable(unsigned int bucket_index, unsigned int element_index) {
    int key=hash_table.at(bucket_index);
    std::vector<int> bucket=cheat_sheet.Get(key);
    return bucket.at(element_index);
}

/*
 * A function which takes three arguments: bucket, element and value.
 * It sets fingerprint stored in specified bucket at specified element to a given value.
 */


void Table::SetElementToTable(unsigned int bucket_index, unsigned int element, int value) {
    int key=hash_table.at(bucket_index);
    hash_table.at(bucket_index)=cheat_sheet.ChangeEntry(key,element,value);
}

/*
 * Function which returns a hash table.
 */


std::vector<int> &Table::GetHashTable() {
    return hash_table;
}

/*
 * Function which has one argument, position of bucket in a hash table (bucket_num)
 * and returns bucket which is located at that position in the hash table.
 */


std::vector<int> Table::GetBucket(int bucket_num) {
    return cheat_sheet.Get(hash_table.at(bucket_num));
}

size_t Table::GetBucketSize(int bucket_num) {
    int key=hash_table.at(bucket_num);
    int empty_entries=cheat_sheet.CountZeroes(key);
    return (B- empty_entries);
}

void Table::AddElementToBucket(int element, int bucket_num) {
    int key=hash_table.at(bucket_num);
    hash_table.at(bucket_num)=cheat_sheet.InsertEntry(key,element);

}

int Table::LookupEntry(int element, int bucket_index){
    return cheat_sheet.LookupEntry(bucket_index, element);
}

void Table::DeleteEntry(int element, int bucket_index){
    hash_table.at(bucket_index)=cheat_sheet.DeleteEntry(bucket_index,element);
}

/*
 * Function which prints a hash table to the screen.
 */

void Table::PrintTableToScreen() {
    std::cout <<endl<< "======HASH TABLE=========\n";
    for (int i =0;i<hash_table.size();i++) {
        int key=hash_table[i];
        cheat_sheet.PrintBucket(key);
    }
    std::cout << "=========================\n";
}

