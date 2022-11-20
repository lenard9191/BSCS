#include <iostream>
#include <assert.h>

using std::cout;

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

    for (int x = 1; x <= 100;  x++) {
        cout << "\t" << head->value  ;
        head = head->next;

    }

    scan->next = NULL;
    scan = head;
    while ( scan){
        head = scan;
        scan = scan->next;
        delete head;

    }

    cout << "\ndone ";

	return 0;
}
