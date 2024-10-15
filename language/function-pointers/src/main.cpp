#include <cstdlib>
#include <ctime>
#include <iostream>

// Using modern C++11 for creating function pointers
#include <functional>

using namespace std;

// At runtime choose one of the two functions
int add(int x, int y) { return x + y; }
int multiply(int x, int y) { return x * y; }

int main() {
  /* This how we traditionally call the functions directly
  cout << add(10, 20) << endl;
  cout << multiply(10, 20) << endl;
  */

  // Definition of function pointer
  int (*some_op)(int, int);

  /* Assining a function with the same signaure to the function pointer
 some_opearation = add;
 cout << some_op(10, 20) << endl;

 some_opearation = multiply;
 cout << some_op(10, 20) << endl;
 // */

  // Dynamically calling the functions using a function pointer
  srand(time(0));

  if (rand() % 2 == 0) {
    some_op = add;
  } else {
    some_op = multiply;
  }
  cout << some_op(10, 20) << endl;

  // Using modern C++11 for creating function pointers
  function<int(int, int)> funcPtr;
  if (rand() % 2 == 0) {
    funcPtr = add;
  } else {
    funcPtr = multiply;
  }
  cout << funcPtr(10, 20) << endl;

  return 0;
}
