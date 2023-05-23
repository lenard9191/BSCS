
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

void merge(int a[], int left_low, int left_high, int right_low, int right_high) 
{ 
    int length = right_high-left_low+1;
    int *temp = new int [length];
    int left = left_low;
    int right = right_low;
    for (int i = 0; i < length; i++) { 
        if (left > left_high)
            temp[i] = a[right++];
        else if (right > right_high)
            temp[i] = a[left++];
        else if (a[left] <= a[right])
            temp[i] = a[left++];
        else
            temp[i] = a[right++]; 
    }
    
    for (int i=0; i< length; i++) {
        a[left_low++] = temp[i];
    }
    
    delete[] temp;

}

void mergeSort(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }
    else {
        int mid = (low+high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr,mid+1,high);
        merge(arr,low,mid,mid+1,high);
    }
}


void displayArr(int arr[], int size) {
    for (int i = 0; i < size; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
    
}
int main()
{
    int size = 1000;
    int arr[size];
    srand(time(NULL));
    for(int i = 0; i < size ; i ++){
        arr[i] = rand()%size;
    };
    clock_t start , finish;
    start = clock();
    mergeSort(arr, 0 , size - 1);
    finish = clock();
    double time_taken = (double(finish - start) / double(CLOCKS_PER_SEC) )* 1000;
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << size;
    return 0;
}
