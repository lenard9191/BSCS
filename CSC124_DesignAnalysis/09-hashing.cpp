#include <iostream>
#include <list>
#include <assert.h>
#include <stdlib.h>

using namespace std;


class hashTable{
    private:
        int buckets;
        int probes;
        list<int> *table;

    public:
        hashTable(int b) {
            buckets = b;
            table = new list<int>[buckets];
            probes = 0;
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
    probes++;
    while(!table[index].empty()){
        index = (index + 1) % buckets;
        probes++;
    }
    table[index].push_back(key);
}

// hx = (hashx + i*i ) % tablesize;
void hashTable::quadraticProbeInsert(int key) {
    int index = key % buckets;
    probes++;
    int orig = key % buckets;
    int i = 1;
    while(!table[index].empty()){
        index = (orig + (i * i) ) % buckets;
        i++;
        probes++;
    }
    table[index].push_back(key);
}

// hx = (hashx + 1*hash2ndx) % tablesize
//primary hash function h(k) = k mod 17
//secondary hash function d(k) = 13 - k mod 13
void hashTable::doubleHashingInsert(int key) {
    int index = key % buckets;
    probes++;
    int orig = key % buckets;
    int i = 1;
    int second_hash = 13 - key % 13;
    while(!table[index].empty()){
        index = (orig + i*second_hash) % buckets;
        i++;
        probes++;
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

    cout << "Total Probes: " << probes << endl;
}
int main() {
    hashTable ht1(17);
    hashTable ht2(17);
    hashTable ht3(17);
    hashTable ht4(17);
    int arr[] = {25, 88, 3, 38, 20, 71, 55, 56, 50, 105};
    int size = sizeof(arr)/sizeof(arr[0]);
    
    for(int i = 0 ; i < size; i++) {
        ht1.insert(arr[i]);
        ht2.linearProbeInsert(arr[i]);
        ht3.quadraticProbeInsert(arr[i]);
        ht4.doubleHashingInsert(arr[i]);
    }

    cout << "Normal Hash \n" << endl;
    ht1.print();

    cout << "\nLinearProbe Hash \n" << endl;
    ht2.print();
    cout << "\nQuadraticProbe Hash \n"  << endl;
    ht3.print();
    cout << "\nDoubleHash \n" << endl;
    ht4.print();
    

    return 0;
}