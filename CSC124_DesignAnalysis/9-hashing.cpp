#include <iostream>
#include <list>
#include <assert.h>
#include <stdlib.h>

using namespace std;


class hashTable{
    private:
        int buckets;
        list<int> *table;
    public:
        hashTable(int b) {
            buckets = b;
            table = new list<int>[buckets];
        }
        void insert(int key);
        void print();
        void linearProbeInsert(int key);
        void quadraticProbeInsert(int key);
        void doubleHashingInsert(int key);
};


void hashTable::insert(int key) {
    int index = key % buckets;
    table[index].push_back(key);
    
}

// hx = (hashx + 0 ) % tablesize;
void hashTable::linearProbeInsert(int key) {
    int index = key % buckets;
    while(!table[index].empty()){
        index = (index + 1) % buckets;
    }
    table[index].push_back(key);
}

// hx = (hashx + i*i ) % tablesize;
void hashTable::quadraticProbeInsert(int key) {
    int index = key % buckets;
    int i = 1;
    while(!table[index].empty()){
        index = (index + (i * i) ) % buckets;
        i++;
    }
    table[index].push_back(key);
}

// hx = (hashx + 1*hash2ndx) % tablesize
//primary hash function h(k) = k mod 17
//secondary hash function d(k) = 13 - k mod 13
void hashTable::doubleHashingInsert(int key) {
    int index = key % buckets;
    int i = 1;
    int second_hash = 13 - key % 13;
    while(!table[index].empty()){
        index = (index + i*second_hash) % buckets;
        i++;
    }
    table[index].push_back(key);

}

void hashTable::print() {
    for(int i = 0; i < buckets; i++) {
        cout<< "Index: " << i << "|";
        for(auto j : table[i]) {
            cout << "-> | " << j << "|";
        }
        cout << endl;
    }
}
int main() {
    hashTable ht(17);
    int arr[] = {25, 88, 3, 38, 20, 71, 55, 56, 50, 105};
    int size = sizeof(arr)/sizeof(arr[0]);
    
    for(int i = 0 ; i < size; i++) {
        ht.doubleHashingInsert(arr[i]);
    }

    
    ht.print();
    

    return 0;
}