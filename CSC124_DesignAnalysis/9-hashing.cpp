// Online C++ compiler to run C++ program online
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
        void insert(int d);
        void print();
        void linearInsert(int d);
        void quadInsert(int d);
        void doubleHashing(int d);
};


void hashTable::insert(int key) {
    int index = key % buckets;
    table[index].push_back(key);
    
}
void hashTable::linearInsert(int key) {
    int index = key % buckets;
    while(!table[index].empty()){
        index = (index + 1) % buckets;
    }
    table[index].push_back(key);
}
void hashTable::quadInsert(int key) {
    return ;
}
void hashTable::doubleHashing(int d ) {
    return;
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
        ht.linearInsert(arr[i]);
    }

    
    ht.print();
    

    return 0;
}