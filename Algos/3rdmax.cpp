#include <iostream>
#include <assert.h>

using namespace std;



//  Sorting Function

void insertionSort(int array[], int size) {
  for (int i = 1; i < size; i++) {
    int key = array[i];
    int j = i - 1;

    // Compare key with each element on the left of it until an element smaller than
    // it is found.
    // For descending order, change key<array[j] to key>array[j].
    while (key > array[j] && j >= 0) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}


/* First Algo where we find the max of the first array and create a second array 
where the previous max is deleted and then third array where the previous max again is deleted */

void firstAlgo(int arr[], int size, int count = 1) {
    int max = arr[0];

    for (int i = 0 ; i < size; i++) {
       cout << arr[i] << " ";

    }   

    for (int i = 1 ; i < size ; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    cout << endl;
    cout << count << " array - maxvalue: " << max << endl;

    if (size <= 0) {
        return;
        
    }

    if (count == 3) {
        cout << "Third Max is: " << max << endl;
        return;
    }

    int index;
    for ( index = 0 ; index < size; index++) {
        if ( arr[index] == max){
            break;
        }
    }

    if (index < size) {
        for (int j = index; j < size-1; j++) {
            arr[j] = arr[j+1];

        }
        size--;

    }

    count++;

    
    firstAlgo(arr, size,count);





}

void secondAlgo(int arr[], int size) {
    int firstmax, secondmax, thirdmax;

}
//Third algo where we use sorting before finding the third max

void thirdAlgo(int arr[], int size) {
    cout << "Printing unsorted array" << endl;
    for ( int i = 0 ; i < size; i ++) {
        cout << arr[i] << " ";
    }

    cout << "\nPrinting sorted array" << endl;
    insertionSort(arr ,size);

    for (int i = 0 ; i < size ; i ++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Third Max is: " << arr[2] << endl;
    

}

int main() {

    int arr[] = { 6, 4, 5, 1, 9, 3, 8, 2};
    int arr2[] = { 6, 4, 5, 1, 9, 3, 8, 2};
    int arr3[] = { 6, 4, 5, 1, 9, 3, 8, 2};

    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "First Algorithm - Using array before creating another array without the previous max" << endl;

    firstAlgo(arr, size);
    cout << "---------------" << endl;
    cout << "---------------" << endl;
    cout << "---------------" << endl;
    secondAlgo(arr2, size);
    cout << "---------------" << endl;
    cout << "---------------" << endl;
    cout << "---------------" << endl;
    cout << "Third Algorithm - Using Sort Before Finding 3rd Max" << endl;
    thirdAlgo(arr3, size);
    

    return 0;

};
