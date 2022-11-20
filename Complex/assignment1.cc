/*

John Lenard R. Requina 2021-0534
CCC102 Laboratory Assignment No. 1
Due: May 23, 2022 (Monday) at 11:55PM

This is the sample program that tests the implementation of the complex
number abtract data type (ADT). You may freely modify this file.
Modifications in this file will not be scored.

Provide the missing implementations of the complex number ADT in the
corresponding definitions file "complex.cc".

To test your implementation, you need to compile this file together with
the complex number ADT module. To compile the program using a C++
project, create a C++ console application project and add the three
files ("assignment1.cc", "complex.cc", and "complex.hh") into the
project. To compile the program using the GCC compiler in the command
line, invoke GCC using the command "gcc -o assignment1 assignment1.cc
complex.cc".

You must submit the whole homework package with your
modifications/additions in the electronic submission. This homework must
comply with the homework policy as stated in the "Assignments" page.
*/

#include <iostream>
#include "complex.hh"

using namespace std;

/*
This is the main function for testing the implementation of the
Complex class. This function is not scored and may be freely modified.
*/
int main(void)
{
    Complex a, b, c;

    cout << "Enter two complex numbers in the format (real, imaginary): ";
    cin >> a;
    cin >> b;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    c = a + b;
    cout << "c = a + b = " << c << endl;

    c = a - b;
    cout << "c = a - b = " << c << endl;

    c = a * b;
    cout << "c = a * b = " << c << endl;

    c = a / b;
    cout << "c = a / b = " << c << endl;

    c = a;
    cout << "c = a = " << c << endl;

    c += b;
    cout << "c += b = " << c << endl;

    c = a;
    c -= b;
    cout << "c -= b = " << c << endl;

    c = a;
    c *= b;
    cout << "c *= b = " << c << endl;

    c = a;
    c /= b;
    cout << "c /= b = " << c << endl;

    c = a;
    if (c == a)
    {
        cout << c << " is equal to " << a << endl;
    }

    if (c != b)
    {
        cout << c << " is not equal to " << b << endl;
    }
    else
    {
        cout << c << " is equal to " << b << endl;
    }


    cout << "conjugate of a is: " << a.conjugate() << endl;
    cout << "conjugate of b is: " << b.conjugate() << endl;
    c = a + b;
    cout << "c = a + b = " << c << endl;
    cout << "conjugate of c is: " << c.conjugate() << endl;

    cout << "\n\n"<< endl;


    cout << "magnitude of a is: " << a.magnitude() << endl;
    cout << "magnitude of b is: " << b.magnitude() << endl;
    c = a + b;
    cout << "c = a + b = " << c << endl;
    cout << "magnitude of c is: " << c.magnitude() << endl;

    cout << "\n\n"<< endl;

    cout << "multiplicative inverse of a is: " << a.inverse() << endl;
    cout << "multiplicative inverse of b is: " << b.inverse() << endl;
    c = a + b;
    cout << "c = a + b = " << c << endl;
    cout << "multiplicative inverse of c is: " << c.inverse() << endl;

    return 0;
}
