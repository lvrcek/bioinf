#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
#include "BucketTable.h"

using namespace std;

bool asc (int i,int j) { return (i<j); }


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

void saveBucket::print(){
        for(int i=0;i<table.size();i++){
            for(int j=0;j<table[i].size();j++){
                cout<<table[i][j]<<" ";
            }
            cout<<endl;
        }
    };

vector<int> saveBucket::get(int index){
//        if(index>=table.size()){
//            cout <<"Out of bounds"<<endl;
//            return nullptr;
//        }
//        else
        return table[index];
};

int saveBucket::findVector(vector<int> target){
        vector<vector<int> >::iterator it;
        it=find(table.begin(),table.end(),target);
        if (it != table.end())
            return (it-table.begin());
        else
            return -1;
     };

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

int saveBucket::countZeroes(int index){
    vector<int> currentBucket=get(index);
    return std::count (currentBucket.begin(), currentBucket.end(), 0);
}

void saveBucket::printBucket(int index){
    vector<int> bucket=get(index);
    for(int i=0;i<bucket.size();i++){
        cout<<bucket[i]<<" ";
    }
    cout<<endl;
}

