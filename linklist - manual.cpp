#include <iostream>
#include <assert.h>


using namespace std;


struct Node{
    int value;
    Node *next;
};


int main (void) {

    Node* first = new Node;
    Node* second = new Node;
    Node* third = new Node;

    assert((first && second && third) != NULL);

    first->value = 1;
    first->next = second;

    second->value = 2;
    second->next = third;

    third->value = 3;
    third->next =  first;

    for ( int k = 0 ; k < 30; k ++ ) {
        cout << first->value << " " ;
        first = first->next;

    }
    delete first, second, third;

    cout << "\nDone"<<endl ;

    return 0;
}

