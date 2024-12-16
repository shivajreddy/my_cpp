import std;
import <print>;

using namespace std;

void allocate_and_deallocate()
{

    /* KEY WAYS TO LOOK AT IT
            new <type>;
            new <type>[];

            <type> can be int, Person, or Person*
    */

    {
        // --------------------------------------------
        // Allocate, after use deallocate set ptr to nullptr
        // --------------------------------------------
        int *ptr { new int }; // Allocated the size_of(int) on heap, and stores
                              // its address on heap

        // Right now *ptr is some random value
        *ptr = 10;

        // Deallocate Memory & Set pointer to nullptr
        delete ptr;
        ptr = nullptr;

        // --------------------------------------------
        // Allocate & Initialize, after use deallocate,
        // set ptr to nullptr
        // --------------------------------------------
        int *ptr2 { new int(10) };
        delete ptr2;
        ptr2 = nullptr;
    }

    {
        // (Pg. 227, Figure 7.6)
        // --------------------------------------------
        // Allocate an array of certain type, after use
        // deallocate set ptr to nullptr
        // --------------------------------------------
        int *arr { new int[5] };

        // Dealocate memory & Set pointer to nullptr
        delete[] arr;
        arr = nullptr;

        // --------------------------------------------
        // Allocate & Initialize, after use deallocate,
        // set ptr to nullptr
        // --------------------------------------------
        int *arr2 { new int[] { 10, 20, 30 } };

        delete arr2;
        arr2 = nullptr;
    }

    {
        // --------------------------------------------
        // Dynamically allocated array after use deallocate
        // set ptr to nullptr
        // --------------------------------------------
        size_t size = 5; // can also be of type int
        int *arr { new int[size] };

        delete[] arr;
        arr = nullptr;
    }
}

// Array of objects
class Simple
{
public:
    Simple() { println("Simple constructor called!"); }
    ~Simple() { println("Simple destructor called!"); }
};

void multiple_allocations()
{
    const size_t size { 5 };

    // Pg. 229
    // Allocate an Array, that will hold pointers
    Simple **mySimplePtrArray { new Simple *[size] };

    // Allocate an object for each pointer
    for (size_t i { 0 }; i < size; ++i) {
        mySimplePtrArray[i] = new Simple {}; // each item is a pointer
    }

    // use mySimplePtrArray

    // Delete each allocated object
    for (size_t i { 0 }; i < size; ++i) {
        delete mySimplePtrArray[i];
        mySimplePtrArray[i] = nullptr;
    }

    // Delete the array itself
    delete[] mySimplePtrArray;
    mySimplePtrArray = nullptr;
}

int main(void)
{
    println("---------------- Memory Management ----------------");
    // allocate_and_deallocate();
    multiple_allocations();

    return 0;
}
