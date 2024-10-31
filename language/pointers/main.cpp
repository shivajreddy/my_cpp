#include <iostream>
#include <vector>

using namespace std;

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void print_vector(vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i] *= 2;
    }
    /*
    for (auto num : vec) {
        cout << num << " ";
    }
    */
    cout << "\n";
}

struct Person {
    const char *name;
    const int age;
    Person(char *name, int age) : name(name), age(age) {};

    void print_details() const { cout << "{" << name << ":" << age << "}\n"; }
};

int main() {

    int x = 10;
    cout << std::is_const<const int>() << endl;
    cout << std::is_const<Person>() << endl;

    const Person p("shiva", 29);
    p.print_details();

    return 0;
}
