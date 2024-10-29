#include <iostream>

using namespace std;

void constant_pointers() {
    // 0. `const` means the value cannot be modified after initialization
    const int x = 5; // x cannot be changed
    // x = 6;        // ERROR:: Cannot assign to variable x

    // x = 6;        // ERR: Cannot assign to variable x

    // x = 6;        // FIX: Cannot assign to variable x

    // 1. Pointer to const value(const data, non - const pointer)
    const int *p1 = &x;
    // *p1 = 100;       // ERROR:: - Ready only value is not assignable
    int y = 20;
    p1 = &y; // OK - can change pointer

    // 2. Const pointer to non - const value(non - const data, const pointer)
    int z = 10;
    int *const p2 = &z;
    *p2 = 100; // OK - can modify value
    // p2 = &y;     // ERROR:: - can't change pointer

    // p3 = &y;   // ERROR:: - can't change pointer
    // 3. Const pointer to const value(const data, const pointer)
    const int *const p3 = &x;
    // *p3 = 100; // ERROR:: - can't modify value
}

#pragma region Pointers Vs Referances
void modifyValue(int *ptr) { // Using pointer
    *ptr = 100;              // Need dereference
}

void modifyValueRef(int &ref) { // Using reference
    ref = 100;                  // No dereference needed
}

void printOnly(const int *ptr) { // Can't modify through ptr
    cout << *ptr << endl;
    // *ptr = 100;                    // ERROR:
}

void printOnlyRef(const int &ref) { // Can't modify through ref
    cout << ref << endl;
    // ref = 100;                     // ERROR:
}

void pointers_vs_referances() {
    // Pointers:
    int x = 5;
    int *ptr = &x; // Must be initialized with address
    ptr = nullptr; // Can be null
    ptr = &x;      // or can be reassigned to something else
    ptr++;         // Can do pointer arithmetic
    int *ptr2;     // Can be declared without initialization
    *ptr = 10;     // Dereference needed to access value

    // References:
    int y = 5;
    int &ref = y; // Must be initialized with variable
                  // Cannot be null
                  // No reference arithmetic
    // int &ref2;    // ERROR:: - must initialize
    ref = 10; // Direct access, no dereference needed

    // Practical example combining these concepts
    modifyValue(&x);   // Need to pass address
    modifyValueRef(x); // Pass direct value

    printOnly(&x);   // Need to pass address
    printOnlyRef(x); // Pass direct value
}
#pragma endregion

int pointers_vs_referances_main() {
    constant_pointers();
    pointers_vs_referances();
    return 0;
}
