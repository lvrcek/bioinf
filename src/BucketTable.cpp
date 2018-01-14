#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
#include "BucketTable.h"


/*Class for optimization of buckets. As arrangement of elements in bucket is not important, just the information if there is particular element in bucket,
that means that different permutations of bucket are all the same. We can sort the bucket in the ascending order. This way we drastically reduce the number
of possible combinations. By the size of F! (where F is length of fingerprint). We can use this information by creating all the possible combinations
that bucket can have, and map it to the key, which in our implementation is index of that combination. Using this, in a bucket we can save only the key of
combination that is appearing in bucket. We sacrifice the preprocessing time for the memory optimization.
*/

using namespace std;

bool asc (int i,int j) { return (i<j); }

/* Helper function that searches for different combinations of elements in bucket*/
void saveBucket::findOneCombination(vector<int> series, int r, int howFarInSeries, vector<int> tmp){
        if(tmp.size() == r){
            global.insert(tmp);
            tmp.clear();
        }
        if(howFarInSeries >= series.size()){
            return ;
        }
        findOneCombination(series, r, howFarInSeries+1, tmp);
        tmp.push_back(series[howFarInSeries]);
        findOneCombination(series, r, howFarInSeries+1, tmp);
    };


/*Constructor for the saveBucket. saveBucket is a  vector if vectors. It is dictionary of key(index) and value(vector). It's values are vectors which represent
possible bucket.*/
saveBucket::saveBucket(int bucketSize, int fingerprintSize){
        vector<int> bag;
        for(int i =0;i<bucketSize-1;i++)
            bag.push_back(0);
        for(int i =0;i<pow(2,fingerprintSize)+1;i++)
            bag.push_back(i);
        vector<int> tmp;
       	findOneCombination(bag, bucketSize, 0, tmp);
        set< vector<int> >::iterator it;
        for(it = global.begin(); it != global.end(); it++){
            table.push_back(*it);
        }

    };

/*Function that prints whole saveBucket, combination: key-value*/
void saveBucket::print(){
        for(int i=0;i<table.size();i++){
            for(int j=0;j<table[i].size();j++){
                cout<<table[i][j]<<" ";
            }
            cout<<endl;
        }
    };

/*returns bucket with key 'index'*/
vector<int> saveBucket::get(int index){
//        if(index>=table.size()){
//            cout <<"Out of bounds"<<endl;
//            return nullptr;
//        }
//        else
        return table[index];
};

/*Function that takes vector and returns it's key*/
int saveBucket::findVector(vector<int> target){
        vector<vector<int> >::iterator it;
        it=find(table.begin(),table.end(),target);
        if (it != table.end())
            return (it-table.begin());
        else
            return -1;
     };


/*Function takes 2 arguments, bucket key and a element.
It returns the the position of element in bucket.*/
int saveBucket::lookupEntry(int index,int fingerprint){
    vector<int> currentBucket=get(index);
    vector<int>::iterator it;
    it=find(currentBucket.begin(),currentBucket.end(),0);
    if (it != currentBucket.end()){
        return (it-currentBucket.begin());
    }
    else
        return -1;
};

/* Function takes 2 arguments: bucket key and a element.
It returns the new key after element is added.
*/
int saveBucket::insertEntry(int index,int fingerprint){
        vector<int> currentBucket=get(index);
        vector<int>::iterator it;
        it=find(currentBucket.begin(),currentBucket.end(),0);
        if (it != currentBucket.end()){
            *it=fingerprint;
            sort(currentBucket.begin(),currentBucket.end(),asc);
            return findVector(currentBucket);
        }
        else
            return -1;
};

/*Function takes 2 arguments: bucket key and a element.
It returns new bucket key after element has been deleted from bucket.*/
int saveBucket::deleteEntry(int index,int fingerprint){
        vector<int> currentBucket=get(index);
        vector<int>::iterator it;
        it=find(currentBucket.begin(),currentBucket.end(),fingerprint);
        if (it != currentBucket.end()){
            *it=0;
            sort(currentBucket.begin(),currentBucket.end(),asc);
            return findVector(currentBucket);
        }
        else
            return -1;
};

/*Function takes 2 arguments: bucket key and a element and a value.
It returns new bucket key after element has swapped with value.*/
int saveBucket::changeEntry(int index,int fingerprint, int value){
        vector<int> currentBucket=get(index);
        vector<int>::iterator it;
        it=find(currentBucket.begin(),currentBucket.end(),fingerprint);
        if (it != currentBucket.end()){
            *it=value;
            sort(currentBucket.begin(),currentBucket.end(),asc);
            return findVector(currentBucket);
        }
        else
            return -1;
};

/* Function takes 1 argument: bucket index.
It returns how many zeroes are in that Bucket.*/
int saveBucket::countZeroes(int index){
    vector<int> currentBucket=get(index);
    return std::count (currentBucket.begin(), currentBucket.end(), 0);
}

/* Function takes 1 argument: bucket index.
It prints the content of bucket to screen*/
void saveBucket::printBucket(int index){
    vector<int> bucket=get(index);
    for(int i=0;i<bucket.size();i++){
        cout<<bucket[i]<<" ";
    }
    cout<<endl;
}

