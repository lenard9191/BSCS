#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

struct link
{
    int value;
    link* next;
};

int main()
{
    int count = 20;
    link* head = new link;
    link * scan = head;

    for(int x = 1; x <= count; x++)
    {

        scan->value = x;

        if (x != count) {

            scan->next = new link;
            assert (scan->next != NULL);
        }
        else {
            scan->next = head;
            break;
        }

        scan = scan->next;

    }

    for (int x = 1; x <= 10;  x++) {
        cout << head << ";" <<head->value<<  " \n" ;
        head = head->next;

    }

    scan->next = NULL;
    scan = head;
    while ( scan){
        link *temp1 = scan;
        scan = scan->next;
        delete temp1;

        i++;

    }

    /*scan = head;
    for (int x = 0; x < count; x++) {
        node * nextNode = scan->next;
        delete scan;
        scan = nextNode;
    }

    */

    cout << "\ndone " << i << " Times" << endl;

	return 0;
}
