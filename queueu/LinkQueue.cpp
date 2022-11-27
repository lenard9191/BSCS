#include <iostream>
#include <assert.h>
#define defaultSize 10

using namespace std;

template <class E>
struct Link
{
    E theElement;
    Link<E> *next;
};

template <class E>
class LQueue

{
    Link<E> *front;
    Link<E> *rear;
    int size;

public:
    // The constructor with initial list size
    LQueue
    (int sz = defaultSize)
    {
        front = rear = new Link<E>;
        size = 0;
    }

    // The copy constructor
    LQueue
    (const LQueue &source)
    {
        
    }

    // The class destructor
    ~LQueue
    ()
    {
        clear();
        delete front;
    }

    // Empty the list
    void clear()
    {
        while ( front->next != NULL){
            rear = front;
            delete rear;
        }
        rear = front;
        size = 0;
    }


    // Return the current element
    E & frontValue() const
    {

        assert(size != 0);
        return front->next->theElement;
    }

    // Insert value at current position
    void enqueue(const E &it)
    {
        rear->next = new Link<E>;
        rear->next->next = NULL;
        rear->next->theElement = it;
        rear = rear->next;
        size++;
    }

    // Remove and return the current element
    E dequeue()
    {
        assert(size != 0);
        Link<E> *temp = front->next;
        E it = temp->theElement;
        front->next = temp->next;
        if ( rear == temp) rear = front;
        delete temp;
        size--;
        return it;
    
    }
    int length() const
    {
        return size;
    }    
};



int main() {
    
    LQueue<int> temp;

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
