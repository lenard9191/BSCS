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


void hashTable::insert(int d) {
    int index = d % buckets;
    table[index].push_back(d);
    
}
void hashTable::linearInsert(int d) {
    return ;
}
void hashTable::quadInsert(int d) {
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
        ht.insert(arr[i]);
    }

    
    ht.print();
    

    return 0;
}