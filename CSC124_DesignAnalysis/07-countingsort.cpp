
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

void displayArr(int arr[], int size) {
    for (int i = 0; i < size; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
    
}


void countSort(int arr[], int size) {

  int arrb[size];
  
  int max = arr[0];

  // Find the largest element of the arr
  for (int i = 1; i < size; i++) {
    if (arr[i] > max)
      max = arr[i];
  }

  int arrc[max];

  for (int i = 0; i <= max; ++i) {
    arrc[i] = 0;
  }

 
  for (int i = 0; i < size; i++) {
    arrc[arr[i]]++;
  }

  for (int i = 1; i <= max; i++) {
    arrc[i] += arrc[i - 1];
  }

  for (int i = size - 1; i >= 0; i--) {
    arrb[arrc[arr[i]] - 1] = arr[i];
    arrc[arr[i]]--;
  }

  for (int i = 0; i < size; i++) {
    arr[i] = arrb[i];
  }
}


int main()
{
    int size = 100000;
    int arr[size];
    srand(time(NULL));
    for(int i = 0; i < size ; i ++){
        arr[i] = rand()%size;
    };
    clock_t start , finish;
    //displayArr(arr,size);
    start = clock();
    countSort(arr, size);
    finish = clock();
    //displayArr(arr,size);
    double time_taken = (double(finish - start) / double(CLOCKS_PER_SEC) )* 1000;
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << size;
    return 0;
}
