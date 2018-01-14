#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include "Table.h"


//saveBucket cheatSheet(4,4);

/*
 * A constructor for class Table. Hash table is declared as vector of m vectors of integers.
 * Each inner vector represents a bucket, meaning it can store at most same number of elements
 * as is number of slots in a bucket (given with a constant B).
 */


Table::Table() : cheatSheet(B,F) {
    this->hashTable.resize(M);
};

/*
 * A default destructor for class Table.
 */

Table::~Table() = default;

/*
 * A function which takes two arguments: bucket and element.
 *  It returns fingerprint stored at specified bucket and position in bucket (element).
 */

int Table::getElementFromTable(unsigned int bucketIndex, unsigned int elementIndex) {
    int key=hashTable.at(bucketIndex);
    std::vector<int> bucket=cheatSheet.get(key);
    return bucket.at(elementIndex);
}

/*
 * A function which takes three arguments: bucket, element and value.
 * It sets fingerprint stored in specified bucket at specified element to a given value.
 */


void Table::setElementToTable(unsigned int bucketIndex, unsigned int element, int value) {
    int key=hashTable.at(bucketIndex);
    hashTable.at(bucketIndex)=cheatSheet.changeEntry(key,element,value);
}

/*
 * Function which returns a hash table.
 */


std::vector<int> &Table::getHashTable() {
    return hashTable;
}

/*
 * Function which has one argument, position of bucket in a hash table (bucketNum)
 * and returns bucket which is located at that position in the hash table.
 */


std::vector<int> Table::getBucket(int bucketNum) {
    return cheatSheet.get(hashTable.at(bucketNum));
}

size_t Table::getBucketSize(int bucketNum) {
    int key=hashTable.at(bucketNum);
    int emptyEntries=cheatSheet.countZeroes(key);
    return (B- emptyEntries);
}

void Table::addElementToBucket(int element, int bucketNum) {
    int key=hashTable.at(bucketNum);
    hashTable.at(bucketNum)=cheatSheet.insertEntry(key,element);

}

int Table::lookUpEntry(int element, int bucketIndex){
    return cheatSheet.lookupEntry(bucketIndex, element);
}

void Table::deleteEntry(int element, int bucketIndex){
    hashTable.at(bucketIndex)=cheatSheet.deleteEntry(bucketIndex,element);
}

/*
 * Function which prints a hash table to the screen.
 */

void Table::printTableToScreen() {
    std::cout <<endl<< "======HASH TABLE=========\n";
    for (int i =0;i<hashTable.size();i++) {
        int key=hashTable[i];
        cheatSheet.printBucket(key);
    }
    std::cout << "=========================\n";
}


//
//int main() {
//    int myints[] = {0,0,0,15};
//    Table tablica;
//
//    tablica.addElementToBucket(1,100);
//    tablica.addElementToBucket(1,110);
//    tablica.addElementToBucket(1,120);
//    tablica.addElementToBucket(1,130);
//    tablica.addElementToBucket(1,140);
//    tablica.addElementToBucket(1,299);
//    tablica.addElementToBucket(3,299);
//    tablica.setElementToTable(299,3,5);


//    for(int i =0;i<tablica.hashTable.size();i++){
//        cout<<tablica.hashTable[i]<<std::endl;
//    }
//    vector<int> temp=tablica.getBucket(299);
//    for(int i =0;i<temp.size();i++){
//        cout<<temp[i]<<" ";
//    }

    //cout<<tablica.getElementFromTable(299,3);

    //tablica.printTableToScreen();

//    std::vector<int> currentBucket(myints, myints + sizeof(myints) / sizeof(int));
//    cout<< cheatSheet.findVector(currentBucket)<<" ";
//    for(int i=0;i<currentBucket.size();i++)
//        cout<<currentBucket[i]<<" ";
//    currentBucket=cheatSheet.get(cheatSheet.insertEntry(cheatSheet.findVector(currentBucket),1));
//    cout<<endl<<cheatSheet.findVector(currentBucket)<<" ";
//    for(int i=0;i<currentBucket.size();i++)
//        cout<<currentBucket[i]<<" ";
//    currentBucket=cheatSheet.get(cheatSheet.insertEntry(cheatSheet.findVector(currentBucket),7));
//    cout<<endl<<cheatSheet.findVector(currentBucket)<<" ";
//    for(int i=0;i<currentBucket.size();i++)
//        cout<<currentBucket[i]<<" ";
//    currentBucket=cheatSheet.get(cheatSheet.insertEntry(cheatSheet.findVector(currentBucket),8));
//    cout<<endl<<cheatSheet.findVector(currentBucket)<<" ";
//    for(int i=0;i<currentBucket.size();i++)
//        cout<<currentBucket[i]<<" ";
//    cout<<endl<<cheatSheet.insertEntry(cheatSheet.findVector(currentBucket),5);
//    cout<<endl<<cheatSheet.deleteEntry(cheatSheet.findVector(currentBucket),8);
//
//
//    //cheatSheet.print();
//	return 0;
//}

