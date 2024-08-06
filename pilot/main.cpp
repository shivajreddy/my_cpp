#include <cstdio>
#include <iostream>

using namespace std;

void print_array(int *arr, int size);

class

    class Person {
 public:
  int age;
  Person(int age) { age = age; }
};

int main() {
  int arr[10] = {0};
  int n = sizeof(arr) / sizeof(arr[0]);

  print_array(arr, n);
  print_array(arr, n);

  Person p1 = Person(39);
  auto p2 = Person(29);

  cout << p1.age << endl;
  cout << p2.age << endl;
}

void print_array(int *arr, int size) {
  for (int i = 0; i < size; i++) printf("%d: %d\n", i, arr[i]);
}
