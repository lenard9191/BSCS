#include <iostream>
#include <assert.h>
#include "Queue.h"

using namespace std;

template <typename E> class AQueue : public Queue {
    private:
        int maxSize; // Maximum size of queue
        int front; // Index of front element
        int rear; // Index of rear element
        E *listArray; // Array holding queue element
    public:
        AQueue(int size =defaultSize) 
        { 
            maxSize = size+1;
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
            maxSize = size+1;
            rear = 0; front = 1;
            listArray = new E[maxSize];
            } 
        void enqueue(const E& it) 
        { 
            Assert(((rear+2) % maxSize) != front, "Queue is full");
            rear = (rear+1) % maxSize; // Circular increment
            listArray[rear] = it;
        }
        E dequeue() 
        { // Take element out
            Assert(length() != 0, "Queue is empty");
            E it = listArray[front];
            front = (front+1) % maxSize; // Circular increment
            return it;
        }
        const E& frontValue() const 
        { // Get front value
            Assert(length() != 0, "Queue is empty");
            return listArray[front];
        }
        virtual int length() const // Return length
        { 
            return ((rear+maxSize) - front + 1) % maxSize; 
        }
};

int main (){

    return 0;

};