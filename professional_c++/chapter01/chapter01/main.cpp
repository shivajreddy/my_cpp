import std;
import <print>;

int main(void) {
  std::println("CHAPTER 1 - Crash Course in C++");
  return 0;

  // Use of Const
  const int x{10};

  // Const with pointers
  int *ip;
  ip = new int[10];

  // Deallocate memory
  delete[] ip;
  ip = nullptr;

  const int *p;
  p = new int[10];

  // Won't compile -> can't assign value
  // p[1] = 20;

  /*
  pointer to non-const value
  const pointer to non-const value
  pointer to const value
  const pointer to const value

  1. When we need a pointer, but don't want to allow mutating the data through
  this pointer (when we put it like this, its so obvious to just a referance
  instead of raw pointer)
  -----------------|
  const <type>*    |
  <type> const*    |= Both are same   <- more prefered way to write
  -----------------
  Exmaple:
  const int* ip;
  ip = new int[10];
  ip[4] = 5;  // C.E

  int const* ip;
  ip = new int[10];
  ip[4] = 5;  // C.E

  */
  int x1{10};
  const int x2{10};

  int y1{20};
  const int y2{20};

  int const *p1;

  p1 = &x1;
  std::println("x1 = {}", x1);
  std::println("*p1 = {}", *p1);

  *p1 += 1;

  const int some_const{20};
  some_const += 1;

  std::println("x1 = {}", x1);
  std::println("*p1 = {}", *p1);

  p1 = &y1;
  std::println("y1 = {}", y1);
  std::println("*p1 = {}", *p1);
}
