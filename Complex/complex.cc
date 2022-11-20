/*

John Lenard R. Requina 2021-0534
CCC102 Laboratory Assignment No. 1
Due: May 23, 2022 (Monday) at 11:55PM

Provide the missing implementations of the complex number abstract data
type (ADT) in this file.

You must submit the whole homework package with your
modifications/additions in the electronic submission. This homework must
comply with the homework policy as stated in the "Assignments" page.
*/

#include <iostream>
#include <math.h>

#include "complex.hh"

using namespace std;

/*
Complete the implementation of the ADT for representing complex numbers
as declared in the header file "complex.hh" here. Implement the
constructors, the accessor functions, the assignment operators, the
complex conjugate method, the multiplicative inverse method, the complex
magnitude method, the arithmetic operators, and the comparison operators
of the Complex class. Read the class declaration in the header file
"complex.hh" for more information.
*/


//Implement the following functions in this file.

// constructors
Complex::Complex(){
    _real = 0;
    _imaginary = 0;
}
Complex::Complex(float r){
    _real = r;
    _imaginary = 0;
}
Complex::Complex(float r, float i){
    _real = r;
    _imaginary = i;

}
Complex::Complex(const Complex &source) {
    _real = source._real;
    _imaginary = source._imaginary;
}

// accessor functions
float Complex::getReal() const{
    return _real;
}
float Complex::getImaginary() const{
    return _imaginary;
}
void Complex::setReal(float real){
    _real = real;
}
void Complex::setImaginary(float imaginary){
    _imaginary = imaginary;
}


// assignment operators
Complex & Complex::operator =(const Complex &source){
    _real = source._real;
    _imaginary = source._imaginary;

    return *this;
}


Complex & Complex::operator +=(const Complex &source){
    _real = _real + source._real;
    _imaginary = _imaginary + source._imaginary;


    return *this;
}

Complex & Complex::operator -=(const Complex &source){
    _real = _real - source._real;
    _imaginary = _imaginary - source._imaginary;

    return *this;
}

Complex & Complex::operator *=(const Complex &source){
    _real = _real * source._real;
    _imaginary = _imaginary * source._imaginary;

    return *this;
}


Complex & Complex::operator /=(const Complex &source){
    _real = _real / source._real;
    _imaginary = _imaginary / source._imaginary;

    return *this;
}


// complex conjugate
Complex Complex::conjugate() const{
    Complex conj;
    conj._real = _real;
    conj._imaginary = -1*_imaginary;

    return conj;


}


// complex multiplicative inverse
Complex Complex::inverse() const{
    float a, b, denomi;
    a = _real;
    b = _imaginary;
    denomi = (a*a) + (b*b);



    float denom = (_real*_real)+(_imaginary*_imaginary);
    cout << "(" << a << "-" << b << "i" << " )/ " << denom << endl;
}


// complex magnitude
float Complex::magnitude() const{
    float mag;
    mag = sqrt((_real*_real)+(_imaginary*_imaginary));

    return mag;
}

// arithmetic operators


Complex operator +(const Complex &left, const Complex &right){
    Complex sum;
    sum = Complex(left.getReal() + right.getReal(), left.getImaginary() + right.getImaginary());
    return sum;

    //return ( Complex (left.getReal() + right.getReal() , left.getImaginary() + right.getImaginary() ));
}


Complex operator -(const Complex &left, const Complex &right){
    Complex diff;
    diff = Complex(left.getReal() - right.getReal(), left.getImaginary() - right.getImaginary());
    return diff;
}
Complex operator *(const Complex &left, const Complex &right){
    Complex prod;
    prod = Complex(left.getReal() * right.getReal(), left.getImaginary() * right.getImaginary());
    return prod;

}
Complex operator /(const Complex &left, const Complex &right){
    Complex qout;
    qout = Complex(left.getReal() / right.getReal(), left.getImaginary() / right.getImaginary());
    return qout;


}



// comparison operators
int operator == (const Complex &left, const Complex &right){

    return (left.getReal() == right.getReal() && left.getImaginary() == right.getImaginary());


}
int operator != (const Complex &left, const Complex &right) {


    return (left.getReal() != right.getReal() || left.getImaginary() != right.getImaginary());


}

/*
Stream input/output implementation:

The following stream inserter (<<) and extractor (>>) operators are
already implemented. You do not need to do anything to the
implementations. The implementations are designed to process complex
numbers in the format (real, imaginary).
*/

// stream inserter implementation
ostream & operator << (ostream &out, const Complex &value)
{
    // stream output of a complex number in the format
	// (real, imaginary)
    out << "(" << value.getReal() << ", " << value.getImaginary() <<
		")";

    return out;
}

// stream extractor implementation
istream & operator >> (istream &in, Complex &destination)
{
    // stream input of complex number
    float real = 0, imaginary = 0;

    char c;

    // read '('
    in >> c;
    if (c == '(')
    {
        // read real part
        in >> real;

        // read ','
        in >> c;
        if (c == ',')
        {
            // read imaginary part
            in >> imaginary;
        }
        else   // no imaginary part
        {
            in.putback(c);
        }

        // read ')'
        in >> c;
        if (c != ')')
        {
            in.putback(c);
        }
    }
    else // no imaginary part
    {
        in.putback(c);
        in >> real;
    }

    // do the assignment
    Complex result(real, imaginary);
    destination = result;

    // return the stream
    return in;
}
