#include "al/core.hpp"
using namespace al;
#include <iostream>
using namespace std;

int main() {
  // we can do arithmetic with vectors
  Vec3f a(1, 0, 0), b(0, 1, 0);
  a.print();
  b.print();
  // {1, 0, 0} {0, 1, 0} 
  
  lerp(a, b, 0.1).print();
  a.lerp(b, 0.1).print();
  // {0.9, 0.1, 0} {0.9, 0.1, 0} 

  a.print();
  b.print();
  // {0.9, 0.1, 0} {0, 1, 0}
}
