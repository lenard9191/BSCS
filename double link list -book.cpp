/*
CCC121 Laboratory Exercise No. 1
Due: November 20, 2022 (Sunday) at 11:55PM
*/

#include <iostream>
#include <assert.h>

using namespace std;

/*
The structure to be used for representing a doubly-linked link. This struct
declaration should not be modified in any way.
*/
template <class E>
struct DLink
{
    E theElement;
    DLink<E> *nextPtr;
    DLink<E> *prevPtr;
};

/*
Complete this implementation variant of the doubly-linked list. Use the same
convention as described in the slides. The DLink declaration to be used here is
just a struct and should not be modified in any way. All of the operations of
the original DLink class must be done in the methods of this class. Use
assertions to ensure the correct operation of this ADT. All memory allocations
should be checked with assertions and all discarded memory must be properly
deallocated.
*/
template <class E>
class DList
{
    DLink<E> *head;
    DLink<E> *tail;
    DLink<E> *curr;
    int cnt;

public:
    // Return the size of the list
    int length() const
    {
        return cnt;
    }

    // The constructor with initial list size
    DList(int size)
    {
        this();
    }

    // The default constructor
    DList()
    {
        cnt = 0;
        head = new DLink<E>;
        tail = new DLink<E>;
        assert((head && tail) != NULL);
        curr = head;
        head->nextPtr = tail;
        tail->prevPtr = head;
        tail->nextPtr = nullptr;
        head->prevPtr = nullptr;
    }

    // The copy constructor
    DList(const DList &source)
    {
        head = new DLink<E>;
        tail = new DLink<E>;

        assert ((head && tail) != NULL);
        curr = head;
        head->nextPtr = tail;
        tail->prevPtr = head;
        tail->nextPtr = nullptr;
        head->prevPtr = nullptr;
        cnt = 0;

        DLink<E> *temp;
        for (temp = source.head; temp->nextPtr != source.tail; temp = temp->nextPtr) {
                append(temp->nextPtr->theElement);
            if (temp == source.curr) curr = tail->prevPtr;
        }
    }

    // The class destructor
    ~DList()
    {
        curr = head;
        while (curr) {
            DLink<E> *temp = curr;
            curr = curr->nextPtr;
            delete temp;
        }
        cnt = 0;
    }

    // Empty the list
    void clear()
    {
        // 0 1 2 3 4 0
        moveToStart();
        while (curr->nextPtr != tail) {
            remove();
        }
    }

    // Set current to first element
    void moveToStart()
    {
        curr = head;
    }

    // Set current element to end of list
    void moveToEnd()
    {
        curr = tail->prevPtr;
    }

    // Advance current to the next element
    void next()
    {
        if (curr == tail) return;
        curr = curr->nextPtr;
    }

    // Return the current element
    E & getValue() const
    {
        assert(curr != NULL);
        if(curr == tail) {
            cout<< "no value after tail \t";
        }
        if (curr->nextPtr == tail){
            cout<< " tail has no value \t";
        }
        return curr->nextPtr->theElement;

    }

    // Insert value at current position
    void insert(const E &it)
    {
        DLink<E> *temp = new DLink<E>;
        assert(temp != NULL);

        temp->theElement = it;
        temp->nextPtr = curr->nextPtr;
        temp->prevPtr = curr;

        if (curr == tail) {
                cout << "cant insert at tail" ;
                return;

        }
        cnt ++;

        curr->nextPtr->prevPtr = temp;
        curr->nextPtr = temp;
    }

    // Append value at the end of the list
    void append(const E &it)
    {
        DLink<E> *temp = new DLink<E>;
        assert(temp != nullptr);

        temp->theElement = it;
        temp->nextPtr = tail;
        temp->prevPtr = tail->prevPtr;

        cnt ++;

        tail->prevPtr->nextPtr = temp;
        tail->prevPtr = temp;
    }

    // Remove and return the current element
    E remove()
    {
        // 0 1 {2} 3 4 0
        if (curr->nextPtr == tail) {
                cout<< "\nCANT REMOVE TAIL";
            return NULL;


        }
        if(curr == tail) {
            cout<< " NOTHING TO REMOVE";
            return NULL;
        }
        // 1 {2} 3 4
        DLink<E> *temp = curr->nextPtr;
        E it = temp->theElement;


        temp->nextPtr->prevPtr = curr;
        curr->nextPtr = temp->nextPtr;
        cout<< "\nREMOVING " << it << endl;
        delete temp;

        cnt--;
        return it;

    }

    // Advance current to the previous element
    void prev()
    {
        if (curr == head) return;
        curr = curr->prevPtr;
    }

    // Return position of the current element
    int currPos() const
    {
        int i;
        DLink<E> *temp = head;

        for (i = 0 ; curr != temp; i++) {
                temp = temp->nextPtr;
        }
        return i;
    }

    // Set current to the element at the given position
    void moveToPos(int pos)
    {
        assert(("OUT OF RANGE",pos >= 0 && pos<=length()));
        curr = head;
        for(int i = 0; i < pos; i++) {
            curr = curr->nextPtr;
        }
    }
};

/*
This is the main function for testing the implementation of the DList class.
This function can be freely modified.
*/
int main(void)
{
    int i;
    DList<int> theList;

    // populate the list


    for (i = 0; i < 10; ++i)
    {
       theList.append(i);
    }
    while (i < 20)
    {
        theList.insert(i);

        ++i;
    }

    // display the contents of the list
    theList.moveToStart();
    cout << "Display Normal\n";
    for (int i = 0; i < theList.length(); i++) {
        cout <<  theList.getValue()<< " ";
        theList.next();
    }
    cout << "\n" << endl;

    // display the contents of the list in reverse order
    theList.moveToEnd();
    cout << "Display Reverse\n";
    for (int i = 0; i < theList.length(); i++) {
        theList.prev();
        cout <<  theList.getValue()<< " ";

    }
    cout << "\n"<< endl;

    // replace the contents of the list
    theList.clear();

    cout<< "\nCreating new list\n"<< endl;
    for (i = 0; i < 10; ++i)
    {
        theList.append(i + 100);
    }

    // display the contents of the list
    theList.moveToStart();
    cout << "Display Normal\n";
    for (int i = 0; i < theList.length(); i++) {
        cout <<  theList.getValue()<< " ";
        theList.next();
    }
    cout << "\n" << endl;

    // display the contents of the list in reverse order
    theList.moveToEnd();
    cout << "Display Reverse\n";
    for (int i = 0; i < theList.length(); i++) {
        theList.prev();
        cout <<  theList.getValue()<< " ";

    }
    cout << "\n"<< endl;

    // remove two elements at the specified position
    theList.moveToPos(5);
    cout << "Current POS: \t" << theList.currPos();
    theList.remove();
    cout << "\n\nCurrent POS: \t" << theList.currPos();
    theList.remove();
    cout << "\n"<< endl;

    // display the contents of the list
    theList.moveToStart();
    cout << "Display Normal\n";
    for (int i = 0; i < theList.length(); i++) {
        cout <<  theList.getValue()<< " ";
        theList.next();
    }
    cout << "\n" << endl;

    // display the contents of the list in reverse order
    theList.moveToEnd();
    cout << "Display Reverse\n";
    for (int i = 0; i < theList.length(); i++) {
        theList.prev();
        cout <<  theList.getValue()<< " ";

    }
    cout << "\n"<< endl;

    theList.moveToPos(0);
    cout << "MOVING TO Current POS: \t" << theList.currPos();
    theList.remove();
    cout<< "\n" << endl;
    theList.moveToEnd();
    cout << "MOVING TO Current POS: \t" << theList.currPos() ;
    theList.remove();
    cout<< "\n" << endl;



    // display the contents of the list
    theList.moveToStart();
    cout << "Display Normal\n";
    for (int i = 0; i < theList.length(); i++) {
        cout <<  theList.getValue()<< " ";
        theList.next();
    }
    cout << "\n" << endl;

    // display the contents of the list in reverse order
    theList.moveToEnd();
    cout << "Display Reverse\n";
    for (int i = 0; i < theList.length(); i++) {
        theList.prev();
        cout <<  theList.getValue()<< " ";

    }
    cout << "\n"<< endl;

    theList.moveToPos(0);
    cout << "MOVING TO Current POS: \t" << theList.currPos() << "\nVALUE: \t" << theList.getValue()<< "\n";
    cout << "ADDING: 1000 ";
    theList.insert(1000);
    cout<< "\n" << endl;

    theList.moveToEnd();
    cout << "MOVING TO Current POS: \t" << theList.currPos() << "\nVALUE: \t" << theList.getValue()<< "\n";
    cout << "ADDING: 1001 ";
    theList.insert(1001);
    cout<< "\n" << endl;

    // display the contents of the list
    theList.moveToStart();
    cout << "Display Normal\n";
    for (int i = 0; i < theList.length(); i++) {
        cout <<  theList.getValue()<< " ";
        theList.next();
    }
    cout << "\n" << endl;

    // display the contents of the list in reverse order
    theList.moveToEnd();
    cout << "Display Reverse\n";
    for (int i = 0; i < theList.length(); i++) {
        theList.prev();
        cout <<  theList.getValue()<< " ";

    }
    cout << "\n"<< endl;

    DList<int> theList2 = theList;


    cout << "THIS IS THE LIST 2: copy constructor check"  << endl;
    theList2.moveToEnd();
    cout << "Display Reverse\n";
    for (int i = 0; i < theList2.length(); i++) {
        theList2.prev();
        cout <<  theList2.getValue()<< " ";

    }

    cout << "\nDone" ;

    return 0;

}
