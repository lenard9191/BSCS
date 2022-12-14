

#include <iostream>
#include <assert.h>

using namespace std;


template <class E>
struct DLink
{
    E theElement;
    DLink<E> *nextPtr;
    DLink<E> *prevPtr;
};


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
        tail = nullptr;
        head = nullptr;
        curr = nullptr;
    }

    // The copy constructor
    DList(const DList &source)
    {
        if (source == NULL) return ;
        curr = source->curr;
        head = source->head;
        tail = source->tail;
        cnt = source->cnt;
    }

    // The class destructor
    ~DList()
    {
        moveToStart();
        // 1, 2 , 3 ,4
        while (curr->nextPtr != nullptr) {

                DLink<E> *temp = curr;
                next();
                delete temp;
                if(curr == tail){
                    delete curr;
                    break;
                }

        }
    }

    // Empty the list
    void clear()
    {
        moveToStart();
        // 1, 2 , 3 ,4
        while (curr->nextPtr != nullptr) {

                DLink<E> *temp = curr;
                next();
                delete temp;
                if(curr == tail){
                    delete curr;
                    break;
                }

        }
        head = nullptr;
        tail = nullptr;
        curr = nullptr;
        cnt = 0;
    }

    // Set current to first element
    void moveToStart()
    {
        curr = head;
    }

    // Set current element to end of list
    void moveToEnd()
    {
        curr = tail;
    }

    // Advance current to the next element
    void next()
    {
        if(curr == tail) return;
        curr = curr->nextPtr;
    }

    // Return the current element
    E & getValue() const
    {
        return curr->theElement;
    }

    // Insert new head;
    void inserthead(const E & it){

        // 1 2 3 4
        DLink<E> *temp = new DLink<E>;
        cnt++;
        assert(temp != NULL);
        temp->theElement = it;
        temp->nextPtr = head;
        temp->prevPtr = nullptr;

        head->prevPtr = temp;
        head = temp;
        curr = head;
        return;


    }
    void insert(const E &it)
    {
        DLink<E> *temp = new DLink<E>;
        cnt++;
        assert(temp != NULL);
        temp->theElement = it;
        temp->nextPtr = curr->nextPtr;
        temp->prevPtr = curr;

        if(head == nullptr) {
                head = temp;
                head->prevPtr = nullptr;
                tail = temp;
                tail->nextPtr = nullptr;
                curr = temp;
                return;
        }

        // {1} 2 3 4
        else if ( curr == tail) {
            temp->nextPtr = nullptr;
            temp->prevPtr = tail;
            curr->nextPtr = temp;
            tail = temp;
            return;
        }
        // 1 2 3 {4}
        if (curr->nextPtr != nullptr) {
            curr->nextPtr->prevPtr = temp;

        }
        curr->nextPtr = temp;

        if(temp->nextPtr == nullptr) tail = temp;;
    }

    // Append value at the end of the list
    void append(const E &it)
    {
        DLink<E> *temp = new DLink<E>;
        assert(temp != nullptr);
        temp->theElement = it;
        temp->nextPtr = nullptr;
        temp->prevPtr = tail;

        cnt++;

        if (head == nullptr) {
                head = temp;
                head->prevPtr = nullptr;
                tail = temp;
                tail->nextPtr = nullptr;
                curr = temp;
                return;
        }


        tail->nextPtr = temp;
        tail = temp;

    }

    // Remove and return the current element
    E remove()
    {
        DLink<E> *temp = curr;
        E it = temp->theElement;
        // |1|, 2 ,3 ,4
        if (temp == head){
            head = temp->nextPtr;
            curr = head;
            delete temp;
            cnt--;
            return it;

        }
        // 1, 2, 3, |4|
        else if ( temp == tail){
                tail = temp->prevPtr;
                curr = tail;
                delete temp;
                cnt--;
                return it;
        }


        temp->prevPtr->nextPtr = temp->nextPtr;
        temp->nextPtr->prevPtr = temp->prevPtr;


        curr = temp->nextPtr;
        delete temp;
        cnt--;
        return it;
    }

    // Advance current to the previous element
    void prev()
    {
        if (curr ==head) return;
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
        moveToStart();
        for(int i = 0; i < pos; i++) {
                next();
        }
    }
    void printNormal() {
        moveToStart();
        cout << "Display in Linear\n"<<endl;

        for (int i = 0; i < length(); i++) {

            cout <<  curr->theElement<< " ";
            next();

        }
        cout << "\n";
    }
    void printReverse()
    {
        moveToEnd();
        cout <<  "\n"<<"Display in Reverse\n"<< endl;
        for ( int i = 0; i < length(); i ++) {
                cout << curr->theElement << " " ;
                prev();
        }
        cout << "\n"<<endl;
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
    theList.printNormal();


    // display the contents of the list in reverse order
    theList.printReverse();

    // replace the contents of the list
    theList.clear();
    cout<< "Creating new list"<< endl;
    for (i = 0; i < 10; ++i)
    {
        theList.append(i + 100);
    }

    // display the contents of the list
    theList.printNormal();

    theList.printReverse();

    // remove two elements at the specified position
    theList.moveToPos(5);
    cout << "Current POS: \t" << theList.currPos() << "\nVALUE: \t" << theList.getValue()<< "\n\n";

    cout << "Removing: " << theList.getValue();
    theList.remove();
    cout << "\nRemoving: " << theList.getValue();
    theList.remove();
    cout << "\n"<< endl;

    theList.printNormal();
    theList.printReverse();


    theList.moveToStart();
    cout << "MOVING TO Current POS: \t" << theList.currPos() << "\nVALUE: \t" << theList.getValue()<< "\n";
    cout << "Removing: " << theList.getValue();
    theList.remove();
    cout<< "\n" << endl;
    theList.moveToEnd();
    cout << "MOVING TO Current POS: \t" << theList.currPos() << "\nVALUE: \t" << theList.getValue()<< "\n";
    cout << "Removing: " << theList.getValue();
    theList.remove();
    cout<< "\n" << endl;
    // display the contents of the list
    theList.printNormal();
    // display the contents of the list in reverse order
    theList.printReverse();

    theList.moveToStart();
    cout << "MOVING TO Current POS: \t" << theList.currPos() << "\nVALUE: \t" << theList.getValue()<< "\n";
    cout << "ADDING: 1000 ";
    theList.insert(1000);
    cout<< "\n" << endl;

    theList.moveToEnd();
    cout << "MOVING TO Current POS: \t" << theList.currPos() << "\nVALUE: \t" << theList.getValue()<< "\n";
    cout << "ADDING: 1001 ";
    theList.insert(1001);
    cout<< "\n" << endl;

    cout << "ADDING NEW HEAD: 143 \n";
    theList.inserthead(143);

    theList.printNormal();

    theList.printNormal();
    theList.printReverse();
    cout << "Done" ;
    return 0;

}
