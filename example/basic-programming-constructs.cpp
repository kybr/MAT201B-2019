#include "al/core.hpp"
using namespace al;

// primitive types
bool b = true;     // or false
char c = 'd';      // 8-bit integer that also does ASCII characters
short s = 65535;   // 16-bit integer
int i = 1;         // 32-bit integer
long l = 2;        // 64-bit integer
float f = 0.123;   // 32-bit "floating point" number
double d = 0.123;  // 64-bit double-precision "floating point" number
long double ld;    // 128-bit float

// class definition....
//
// class class-name { class-body };
//
class Point       // class class-name
{                 // begining of scope
 public:          // accessibility (public, private (the default), protected)
  float x, y, z;  // member variables
  Point() {}      // constructor; a function called when an object is made
  void print() {  // member function also called a "method"
    printf("%f,%f,%f\n", x, y, z);
  }
};  // end of scope and semicolon
// a struct is the same as class with everything public

// function definition....
//
// return-type function-name ( argument-list )
// { function-body }
//
int add(int a, int b)      // function "signature": return-type, function-name, argument-list
{                          // begining of scope
  printf("add called\n");  // statement; "side effect"
  return a + b;            // return-statement
                           // end of scope
}
// functions can only return a single thing

//
int main() {
  Point p;
  p.x = 0.1;  // public member accessed with "."
  p.y = -0.1;
  p.z = 0;
  p.print();
  //
}
