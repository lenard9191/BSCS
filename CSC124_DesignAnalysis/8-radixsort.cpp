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
int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
 

void countSort(int arr[], int n, int exp)
{
    int output[n]; 
    int i, count[10] = { 0 };
 

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 

void radixsort(int arr[], int n)
{

    int m = getMax(arr, n);
 

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main()
{
    int size = 500000;
    int arr[size];
    srand(time(NULL));
    for(int i = 0; i < size ; i ++){
        arr[i] = rand()%size;
    };
    clock_t start , finish;
    //displayArr(arr,size);
    start = clock();
    radixsort(arr, size);
    finish = clock();
    //displayArr(arr,size);
    double time_taken = (double(finish - start) / double(CLOCKS_PER_SEC) )* 1000;
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << size;
    return 0;
}