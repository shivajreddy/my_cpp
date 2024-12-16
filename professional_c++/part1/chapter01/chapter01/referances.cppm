export module referances_mod;

import std;
import <print>;

using namespace std;

export void referances()
{
    println(" ---------------- Referances ---------------- ");

    // int &unnamedRef { 5 }; // C.E
    const int &uRef {5};

    /*
    How to read this
    int &r {x};   // r is a is a refarance to int
    const int &r {x};   // r is a is a refarance to const int (almost from right
                        // to left reading except for cosnt word)
    */

    println("{}", uRef);

    pair myPair {"hello there", 10};
    auto [a, b] {myPair}; // Decompose using structured bindings
    println("{}, {}", a, b);
    a = "shiva";
    b = 20;
    println("{}, {}", a, b);

    auto &[aa, bb] {myPair}; // Decompose into references-to-non-const
    println("{}, {}", aa, bb);
    aa = "shiva";
    bb = 20;
    println("{}, {}", aa, bb);

    pair myPair3 {"Helloooooooooo", 10000000};
    const auto &[aaa, bbb] {myPair3}; // Decompose into references-to-non-const
    println("{}, {}", aaa, bbb);
    // aaa = "shiva";
    // bbb = 20;
    // println("{}, {}", aaa, bbb);
}

/*
// -----------------------------------------------------------
// NOTES
// -----------------------------------------------------------
-   Referances must always be initialized when declared, but
    for Data members (i.e., properties in class they can be initialized
    at constructor leve) because class is just the blueprint
-
*/

// Referance data members
class Person
{
private:
    int &m_ref; // Can be initialized in the constructor

public:
    Person(int &ref) : m_ref {ref} {}
};
