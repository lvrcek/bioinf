#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>

using namespace std;


class saveBucket{

    vector<vector<int> > table;
    set< vector<int> > global;

    void findOneCombination(vector<int> series, int r, int howFarInSeries, vector<int> tmp){
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
    }


public:
    saveBucket(int bucketSize, int fingerprintSize){
        vector<int> bag;
        for(int i =0;i<bucketSize-1;i++)
            bag.push_back(0);
        for(int i =0;i<pow(2,fingerprintSize);i++)
            bag.push_back(i);
        vector<int> tmp;
       	findOneCombination(bag, bucketSize, 0, tmp);
        set< vector<int> >::iterator it;
        for(it = global.begin(); it != global.end(); it++){
            table.push_back(*it);
        }

    }

    void print(){
        for(int i=0;i<table.size();i++){
            for(int j=0;j<table[i].size();j++){
                cout<<table[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    vector<int> get(int index){
//        if(index>=table.size()){
//            cout <<"Out of bounds"<<endl;
//            return nullptr;
//        }
//        else
        return table[index];
    }
    int findVector(vector<int> target){
        vector<vector<int> >::iterator it;
        it=find(table.begin(),table.end(),target);
        if (it != table.end())
            return (it-table.begin());
        else
            return -1;
    }
};


int main() {
    saveBucket tablica(4,4);
    //int myints[] = {12,13,14,15};
    //vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
    //cout<< tablica.findVector(fifth);
    tablica.print();
	return 0;
}
