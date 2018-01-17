x#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
#include "bucket_table.h"


/*Class for optimization of buckets. As arrangement of elements in bucket is not important, just the information if there is particular element in bucket,
that means that different permutations of bucket are all the same. We can sort the bucket in the ascending order. This way we drastically reduce the number
of possible combinations. By the size of F! (where F is length of fingerPrint). We can use this information by creating all the possible combinations
that bucket can have, and map it to the key, which in our implementation is index of that combination. Using this, in a bucket we can save only the key of
combination that is appearing in bucket. We sacrifice the preprocessing time for the memory optimization.
*/

using namespace std;

bool asc (int i,int j) { return (i<j); }

/* Helper function that searches for different combinations of elements in bucket*/
void SaveBucket::FindOneCombination(vector<int> series, int r, int how_far_in_series, vector<int> tmp){
        if(tmp.size() == r){
            global.insert(tmp);
            tmp.clear();
        }
        if(how_far_in_series >= series.size()){
            return ;
        }
        FindOneCombination(series, r, how_far_in_series+1, tmp);
        tmp.push_back(series[how_far_in_series]);
        FindOneCombination(series, r, how_far_in_series+1, tmp);
    };


/*Constructor for the SaveBucket. SaveBucket is a  vector if vectors. It is dictionary of key(index) and value(vector). It's values are vectors which represent
possible bucket.*/
SaveBucket::SaveBucket(int bucket_size, int fingerprint_size){
        vector<int> bag;
        for(int i =0;i<bucket_size-1;i++)
            bag.push_back(0);
        for(int i =0;i<pow(2,fingerprint_size)+1;i++)
            bag.push_back(i);
        vector<int> tmp;
       	FindOneCombination(bag, bucket_size, 0, tmp);
        set< vector<int> >::iterator it;
        for(it = global.begin(); it != global.end(); it++){
            table.push_back(*it);
        }

    };

/*Function that Prints whole SaveBucket, combination: key-value*/
void SaveBucket::Print(){
        for(int i=0;i<table.size();i++){
            for(int j=0;j<table[i].size();j++){
                cout<<table[i][j]<<" ";
            }
            cout<<endl;
        }
    };

/*returns bucket with key 'index'*/
vector<int> SaveBucket::Get(int index){
//        if(index>=table.size()){
//            cout <<"Out of bounds"<<endl;
//            return nullptr;
//        }
//        else
        return table[index];
};

/*Function that takes vector and returns it's key*/
int SaveBucket::FindVector(vector<int> target){
        vector<vector<int> >::iterator it;
        it=find(table.begin(),table.end(),target);
        if (it != table.end())
            return (it-table.begin());
        else
            return -1;
     };


/*Function takes 2 arguments, bucket key and a element.
It returns the the position of element in bucket.*/
int SaveBucket::LookupEntry(int index,int fingerprint){
    vector<int> current_bucket=Get(index);
    vector<int>::iterator it;
    it=find(current_bucket.begin(),current_bucket.end(),fingerprint);
    if (it != current_bucket.end()){
        return (it-current_bucket.begin());
    }
    else
        return -1;
};

/* Function takes 2 arguments: bucket key and a element.
It returns the new key after element is added.
*/
int SaveBucket::InsertEntry(int index,int fingerprint){
        vector<int> current_bucket=Get(index);
        vector<int>::iterator it;
        it=find(current_bucket.begin(),current_bucket.end(),0);
        if (it != current_bucket.end()){
            *it=fingerPrint;
            sort(current_bucket.begin(),current_bucket.end(),asc);
            return FindVector(current_bucket);
        }
        else
            return -1;
};

/*Function takes 2 arguments: bucket key and a element.
It returns new bucket key after element has been deleted from bucket.*/
int SaveBucket::DeleteEntry(int index,int fingerPrint){
        vector<int> current_bucket=Get(index);
        vector<int>::iterator it;
        it=find(current_bucket.begin(),current_bucket.end(),fingerPrint);
        if (it != current_bucket.end()){
            *it=0;
            sort(current_bucket.begin(),current_bucket.end(),asc);
            return FindVector(current_bucket);
        }
        else
            return -1;
};

/*Function takes 2 arguments: bucket key and a element and a value.
It returns new bucket key after element has swapped with value.*/
int SaveBucket::ChangeEntry(int index,int fingerPrint, int value){
        vector<int> current_bucket=Get(index);
        vector<int>::iterator it;
        it=find(current_bucket.begin(),current_bucket.end(),fingerPrint);
        if (it != current_bucket.end()){
            *it=value;
            sort(current_bucket.begin(),current_bucket.end(),asc);
            return FindVector(current_bucket);
        }
        else
            return -1;
};

/* Function takes 1 argument: bucket index.
It returns how many zeroes are in that Bucket.*/
int SaveBucket::CountZeroes(int index){
    vector<int> current_bucket=Get(index);
    return std::count (current_bucket.begin(), current_bucket.end(), 0);
}

/* Function takes 1 argument: bucket index.
It Prints the content of bucket to screen*/
void SaveBucket::PrintBucket(int index){
    vector<int> bucket=Get(index);
    for(int i=0;i<bucket.size();i++){
        cout<<bucket[i]<<" ";
    }
    cout<<endl;
}
