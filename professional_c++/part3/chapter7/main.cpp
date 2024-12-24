#include <iostream>
#include <memory>
#include <ostream>
#include <unordered_map>

using namespace std;

class Person
{
public:
    Person() { cout << "person creation" << endl; }
    ~Person() { cout << "person destruction" << endl; }

    void go() {}
};

int main()
{
    // Unique Pointer
    unique_ptr<Person> p = make_unique<Person>();
    cout << "hi" << endl;
    p->go();
}

class HashMap
{
private:
    size_t capacity;

public:
};
