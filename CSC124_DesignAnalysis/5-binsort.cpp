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

void binSort(int arr[], int n) {
    int i, j;
    int min_val = arr[0], max_val = arr[0];
 
    // find the minimum and maximum values in the array
    for (i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        } else if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
 
    // create a temporary array of size max_val - min_val + 1
    int *temp = new int[max_val - min_val + 1];
    for (i = 0; i < max_val - min_val + 1; i++) {
        temp[i] = 0;
    }
 
    // count the occurrences of each element in the array
    for (i = 0; i < n; i++) {
        temp[arr[i] - min_val]++;
    }
 
    // overwrite the input array with the sorted values
    for (i = min_val, j = 0; i <= max_val; i++) {
        while (temp[i - min_val] > 0) {
            arr[j++] = i;
            temp[i - min_val]--;
        }
    }
 
    // free the temporary array
    delete [] temp;
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
    binSort(arr, size);
    finish = clock();
    //displayArr(arr,size);
    double time_taken = (double(finish - start) / double(CLOCKS_PER_SEC) )* 1000;
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << size;
    return 0;
}