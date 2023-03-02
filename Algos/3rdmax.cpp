#include <iostream>
#include <assert.h>

using namespace std;



//  Sorting Function

void insertionSort(int array[], int size) {
  for (int i = 1; i < size; i++) {
    int key = array[i];
    int j = i - 1;

    while (key > array[j] && j >= 0) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}


/* First Algo where we find the max of the first array and create a second array 
where the previous max is deleted and then third array where 
the previous max again is deleted using recursion */

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

/* Second algo where the first three elements are the first , second, and third max
and then loop through the remaining items in the array and replace the lowest of the first three */


void secondAlgo(int arr[], int size) {
    int firstmax, secondmax, thirdmax;

    cout << "Second Algorithm" << endl;

    firstmax = arr[0];
    secondmax = arr[1];
    thirdmax = arr[2];

    cout << "~Printing Array~ " << endl; 

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";

    }
    cout << endl;

/*
    for ( int i = 3 ; i < size ; i++) {
        if (firstmax > secondmax && firstmax > thirdmax) {
            if (secondmax < thirdmax) {
                thirdmax = thirdmax + secondmax;
                secondmax = thirdmax - secondmax;
                thirdmax = thirdmax - secondmax;
        }
        }
        else if ( secondmax > firstmax && secondmax > thirdmax) {
            secondmax = secondmax + firstmax;
            firstmax = secondmax - firstmax;
            secondmax = secondmax - firstmax;
            if (secondmax < thirdmax) {
                thirdmax = thirdmax + secondmax;
                secondmax = thirdmax - secondmax;
                thirdmax = thirdmax - secondmax;
            }
        }
        else{
            thirdmax = thirdmax + firstmax;
            firstmax = thirdmax - firstmax;
            thirdmax = thirdmax - firstmax;
            if (secondmax < thirdmax) {
                thirdmax = thirdmax + secondmax;
                secondmax = thirdmax - secondmax;
                thirdmax = thirdmax - secondmax;
            }
        }


        if (arr[i] > thirdmax) {
            thirdmax = arr[i];
        }



    }

    cout << "Third Max is : " << thirdmax << endl;

*/
    for ( int i = 3 ; i < size ; i++) {
        
        if ( arr[i] > firstmax) {
            if ( secondmax < firstmax && secondmax < thirdmax)  {
                secondmax = arr[i];
            }
            else if ( thirdmax < firstmax && thirdmax < secondmax){
                thirdmax = arr[i];
            }
            else {
                firstmax = arr[i];
            }
        }
        else if ( arr[i] > secondmax) {
            if ( firstmax < secondmax && firstmax < thirdmax)  {
                firstmax = arr[i];
            }
            else if ( thirdmax < firstmax && thirdmax < secondmax){
                thirdmax = arr[i];
            }
            else {
                secondmax = arr[i];
            }
        }
        else if ( arr[i] > thirdmax){
            if ( firstmax < secondmax && firstmax < thirdmax)  {
                firstmax = arr[i];
            }
            else if ( secondmax < firstmax && secondmax < thirdmax){
                secondmax = arr[i];
            }
            else {
                thirdmax = arr[i];
            }
        }
        cout << " Operation: " << i <<endl;
        cout << "FirstMAX: " << firstmax << " SecondMax: " << secondmax << " ThirdMax: " << thirdmax << endl;
        
    }
    int lowest = (firstmax < secondmax && firstmax < thirdmax) ? firstmax : ( (secondmax < firstmax && secondmax < thirdmax ) ? secondmax: thirdmax) ;
    cout << "Third Max is : " << lowest << endl;

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

    int size = 10;
    int arr[size];
    int arr2[size];
    int arr3[size];
    for ( int i = 0; i < size ; i++) {
        arr[i] = rand()%100;
        arr2[i] = arr[i];
        arr3[i] = arr[i];
        

    }



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
