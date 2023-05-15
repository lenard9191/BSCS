#include <iostream>
#include <algorithm>
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
void bucketSort(int arr[], int n)
{
    int maxVal = *max_element(arr, arr + n);
    int minVal = *min_element(arr, arr + n);
    int bucketRange = maxVal - minVal + 1;
    int bucket[bucketRange];
  
    fill_n(bucket, bucketRange, 0);
  
    for (int i = 0; i < n; i++)
        bucket[arr[i] - minVal]++;
  
    for (int i = 0, j = 0; i < bucketRange; i++) {
        while (bucket[i] > 0) {
            arr[j++] = i + minVal;
            bucket[i]--;
        }
    }
}
  
int main()
{
    int size = 500000;
    int arr[size];
    srand(time(NULL));
    for(int j = 0; j < 10; j++) {
        for(int i = 0; i < size ; i ++){
            arr[i] = rand()%size;
        };
        clock_t start , finish;
        //displayArr(arr,size);
        start = clock();
        bucketSort(arr, size);
        finish = clock();
        //displayArr(arr,size);
        double time_taken = (double(finish - start) / double(CLOCKS_PER_SEC) )* 1000;
        cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " millisec" << endl;
        cout << "SIZE: " << size << endl;
        
    }

    return 0;
}