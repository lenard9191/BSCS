#include <iostream>
#include <assert.h>
#include "stack.h"
#define defaultSize 10

using namespace std;

template <typename E> class Link {
  public:
    E element;
    Link *next;

    Link(const E& value, Link* nextval = NULL){
      element = value;
      next = nextval;
    }

};


template <typename E>
class LStack : public Stack<E>
{
private:
  Link<E> * top;
  int size;

public:
  LStack(int sz = defaultSize)
  {
    size = 0;
    top = NULL;
  }

  ~LStack()
  {
    clear();
  }

  void clear()
  {
    while (top != NULL) {
      Link<E> *temp = top;
      top = top->next;
      delete temp;
    }
    size = 0;
  }

  void push(const E &it)
  {
    top = new Link<E>(it,top);
    assert(top != NULL);
    size++;
  }

  E pop()
  {
    assert(top != NULL);
    E it = top->element;
    Link<E> *temp = top->next;
    top = temp;

    delete top;
    size--;
    return it;
  }

  const E &topValue() const
  {
    assert(top != 0);
    return top->element;
  }

  int length() const
  {
    return size;
  }

  void print()
  {
    Link<E> *temp = top;
    for (int i = 0; temp != NULL; i++)
    {

      cout << temp->element << " ";
      temp = temp->next;

    }
    cout<< endl;
  }
};

int main()
{
    LStack<int> stack;

    for ( int i = 1; i <= 3; i++) {
        stack.push(i);
        cout<< "Pushing ..." << i << endl;

    }
    cout << "the size of stack is : " << stack.length() << endl;

    stack.print();
    stack.clear();
    cout << "clearing stack: " << endl ;
    
    cout << "the size of stack is : " << stack.length() << endl;

    for( int i = 4; i < 9; i++) {
        stack.push(i);
        cout<< "Pushing ..." << i << endl;
    }
    cout << "the size of stack is : " << stack.length() << endl;

    cout << "The top value is : " << stack.topValue() << endl;
    cout << "popping 8...\n";
    stack.pop();
    cout << "popping 7...\n";
    stack.pop();
    cout << "popping 6...\n";
    stack.pop();
    cout << "the size of stack is : " << stack.length() << endl;
    cout << "clearing stack: " << endl ;
    stack.clear();
    cout << "the size of stack is : " << stack.length() << endl;
    return 0;
}