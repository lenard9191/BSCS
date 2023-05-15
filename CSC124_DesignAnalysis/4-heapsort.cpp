

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

void heapify(int arr[], int n, int i)
{
	int largest = i; 
	int l = 2*i + 1; 
	int r = 2*i + 2; 

	
	if (l < n && arr[l] > arr[largest])
		largest = l;

	
	if (r < n && arr[r] > arr[largest])
		largest = r;

	
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		
		heapify(arr, n, largest);
	}
}


void heapSort(int arr[], int n)
{
	
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	
	for (int i=n-1; i>=0; i--)
	{
		
		swap(arr[0], arr[i]);

		
		heapify(arr, i, 0);
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
    heapSort(arr, size);
    finish = clock();
    double time_taken = (double(finish - start) / double(CLOCKS_PER_SEC) )* 1000;
    //displayArr(arr,size);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) << " millisec" << endl;
    cout << "SIZE: " << size;
    return 0;
}
