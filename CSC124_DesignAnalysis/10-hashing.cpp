#include <iostream>
#include <list>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;


class hashTable{
    private:
        int buckets;
        int probes;
        list<int> *table;

    public:
        bool isPrime(int n) {
            if (n <= 1){
                return false;
            }
            if (n <= 3) {
                return true;
            }
            if (n % 2 == 0 || n % 3 == 0 ) {
                return false;
            }
            for ( int i = 5; i * i <= n; i += 6) {
                if (n % i == 0 || n % (i +2) == 0) {
                    return false;
                }
            }
            return true;
        }

        hashTable(int b) {
            int newSize = static_cast<int>(b * 1.3);
            while(!isPrime(newSize)){
                newSize++;
            }
            buckets = newSize;
            table = new list<int>[buckets];
            probes = 0;
        }
        ~hashTable() {
            delete []table;

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
    int max_size = 70000;
    hashTable ht1(max_size);
    hashTable ht2(max_size);
    hashTable ht3(max_size);
    hashTable ht4(max_size);
    int arr[max_size];
    srand(time(NULL));
    
    for(int i = 0 ; i < max_size; i++) {
        arr[i] = rand()%max_size;
        ht1.insert(arr[i]);
    }
    // for (int i = 0; i < max_size; i++) {
    //     ht1.insert(arr[i]);
    // }
    clock_t start1,start2,start3, finish1,finish2,finish3;

    start1 = clock();
    for ( int i = 0; i < max_size; i++) {
        ht2.linearProbeInsert(arr[i]);
    }
    finish1 = clock();

    double time_taken1 = (double(finish1 - start1) / double(CLOCKS_PER_SEC) )* 1000;
    cout << "Time taken by linearProbeInsert is : " << fixed << time_taken1 << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << max_size << endl;

    start2 = clock();
    for ( int i = 0; i < max_size; i++){
        ht3.quadraticProbeInsert(arr[i]);
    }
    finish2 = clock();
    double time_taken2 = (double(finish2 - start2) / double(CLOCKS_PER_SEC) )* 1000;
    cout << "Time taken by quadraticProbeInsert is : " << fixed << time_taken2 << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << max_size << endl;

    start3 = clock();
    for (int i = 0; i < max_size; i++){
        ht4.doubleHashingInsert(arr[i]);
    }
    finish3 = clock();
    double time_taken3 = (double(finish3 - start3) / double(CLOCKS_PER_SEC) )* 1000;
    cout << "Time taken by doubleHashInsert is : " << fixed << time_taken3 << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << max_size << endl;

    // cout << "Normal Hash \n" << endl;
    // ht1.print();

    // cout << "\nLinearProbe Hash \n" << endl;
    // ht2.print();
    // cout << "\nQuadraticProbe Hash \n"  << endl;
    // ht3.print();
    // cout << "\nDoubleHash \n" << endl;
    // ht4.print();
    
    
    return 0;
}