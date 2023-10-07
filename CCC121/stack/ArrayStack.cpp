#include <iostream>
#include <assert.h>
#include "stack.h"
#define defaultSize 10

using namespace std;



template <typename E>
class AStack : public Stack<E>
{
private:
  int maxSize;
  int top;
  E *listArray;

public:
  AStack(int size = defaultSize)
  {
    maxSize = size;
    top = 0;
    listArray = new E[size];
  }

  ~AStack()
  {
    delete[] listArray;
  }

  void clear()
  {
    delete [] listArray;
    top = 0;
    listArray = new E[maxSize];
  }

  void push(const E &it)
  {
    assert((top != maxSize));
    listArray[top++] = it;
  }

  E pop()
  {
    assert(top != 0);
    return listArray[--top];
  }

  const E &topValue() const
  {
    assert(top != 0);
    return listArray[top - 1];
  }

  int length() const
  {
    return top;
  }

  void print()
  {
    for (int i = 0; i < top; i++)
    {
      cout << listArray[i] << " ";
    }
    cout<< endl;
  }
};

int main()
{
    AStack<int> stack;

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