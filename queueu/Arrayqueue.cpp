#include <iostream>
#include <assert.h>
#include "Queue.h"
#define defaultSize  10

using namespace std;

template <typename E> class AQueue : public Queue<E> {
    private:
        int maxSize; // Maximum size of queue
        int front; // Index of front element
        int rear; // Index of rear element
        E *listArray; // Array holding queue element
    public:
        AQueue() 
        { 
            maxSize = defaultSize+1;
            rear = 0; front = 1;
            listArray = new E[maxSize];
        }
        ~AQueue() 
        { 
            delete [] listArray; 
        } 
        void clear() 
        { 
            delete [] listArray;
            maxSize = defaultSize+1;
            rear = 0; front = 1;
            listArray = new E[maxSize];
            } 
        void enqueue(const E& it) 
        { 
            assert(((rear+2) % maxSize) != front);
            rear = (rear+1) % maxSize; // Circular increment
            listArray[rear] = it;
        }
        E dequeue() 
        { // Take element out
            assert(length() != 0);
            E it = listArray[front];
            front = (front+1) % maxSize; // Circular increment
            return it;
        }
        const E& frontValue() const 
        { // Get front value
            assert(length() != 0);
            return listArray[front];
        }
        virtual int length() const // Return length
        { 
            return ((rear+maxSize) - front + 1) % maxSize; 
        }
};

int main (){
    AQueue<int> temp;

    for (int i = 1; i <= 5; i++){
        temp.enqueue(i);
        cout<< "Queueing: " << i << endl;
    }



    cout << "two numbers has been dequed" << endl;
    temp.dequeue();
    temp.dequeue();

    cout << "Queue lengh is: " <<temp.length () << endl;
    cout << "the new front value is: " << temp.frontValue() << endl;

    cout << "clearing the queue" << endl;
    temp.clear();

    
    return 0;

};