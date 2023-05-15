

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

void shellSort(int arr[], int size) {
    for(int gap = size/2; gap >0; gap = gap/2){
        for (int i = gap; i < size; i++) {
            for (int j = i; j >= gap; j= j - gap) {
                if (arr[j] < arr[j-gap]){
                    int temp = arr[j-gap];
                    arr[j-gap] = arr[j];
                    arr[j] = temp;
                }
                else
                    break;
            }
            
        }
    }
}


void displayArr(int arr[], int size) {
    for (int i = 0; i < size; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
    
}

bool isSorted(int arr[], int size){
     for (int i = 0 ; i < size-1 ; i++) {
        if (arr[i] > arr[i+1]){
            return false;
        }
    }
    return true;
}

int main()
{
    int size = 100;
    int arr[size];
    srand(time(NULL));
    for(int i = 0; i < size ; i ++){
        arr[i] = rand()%size;
    };
    //displayArr(arr,size);
    clock_t start , finish;
    start = clock();
    shellSort(arr, size);
    finish = clock();
    double time_taken = (double(finish - start) / double(CLOCKS_PER_SEC) )* 1000;
    //displayArr(arr,size);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << size;
    return 0;
}
