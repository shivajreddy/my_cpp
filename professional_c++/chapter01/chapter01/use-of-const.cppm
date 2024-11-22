export module use_of_const;

import std;
import <print>;

using namespace std;

export void use_of_const()
{
    // ----------------------------------------------------------------------
    // NOTE : Reading pointers
    // ----------------------------------------------------------------------
    // Read the declarations from right-to-left

    int *const p1 {nullptr}; // read as, p1 is a constant pointer to an integer

    int const *p2 {nullptr}; // read as, p2 is a pointer to a constant integer

    const int *p3 {nullptr}; // read as, p3 is  pointer to a int constant

    // For all the three above cases, VisualStudio will move * the proper
    // position
    /// Example:
    // int* const p {nullptr};      // Once you hit save, this line
    // int *const p {nullptr};      // will be changed to this line, so that
    // you can read as p is a constant pointer to an integer

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


    // 1. Goal: Read only pointer
    // The pointer can be changed to point others, but can't change the
    // data through the pointer make the pointer as const, so that it can not
    int x {10};

    int const *ptr {nullptr};

    ptr = &x;
    std::println("x1 = {}", x);
    std::println("*p1 = {}", *ptr);


    // 2. Goal: make the pointer as const, so that it can not point to something
    // else once

    int *const p2 {nullptr};
    // const int *p2 {nullptr}; is also valid, but not very clear

    int x2 = 100;
    /*
    p2 = &x2; // You can directly initialize it, but since it was alraedy
              // initialized cant point to something else

    int *const p {&x};  // First initialization
    p = &y;             // C.E This variable holds a memory address, and can't
                        // put another value (i.e., another memory address) for
                        // this variable


    */
}

class AirlineTicket
{
public:
public:
    double calculatePriceInDollars() const;
    std::string getPassengerName() const; // 1. must be added to declaration
    void setPassengerName(std::string name);
    int getNumberOfMiles() const;
    void setNumberOfMiles(int miles);
    bool hasEliteSuperRewardsStatus() const;
    void setHasEliteSuperRewardsStatus(bool status);

private:
    std::string m_passengerName {"Unknown Passenger"};
    int m_numberOfMiles {0};
    bool m_hasEliteSuperRewardsStatus {false};
};

// 2. must be added to definition, if you dont put it here, you will
// get CE, saying it was declared as const so you must define as const too
std::string AirlineTicket::getPassengerName() const
{
    std::println(".");
    return m_passengerName;
}
