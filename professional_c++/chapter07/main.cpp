import std;
import <print>;

using namespace std;

int main(void)
{
    println(" ---------------- Memory Management ---------------- ");

    {
        // --------------------------------------------
        // Allocate, after use deallocate set ptr to nullptr
        // --------------------------------------------
        int *ptr {new int}; // Allocated the size_of(int) on heap, and stores
                            // its address on heap

        // Deallocate Memory & Set pointer to nullptr
        delete ptr;
        ptr = nullptr;

        // --------------------------------------------
        // Allocate & Initialize, after use deallocate,
        // set ptr to nullptr
        // --------------------------------------------
        int *ptr2 {new int(10)};
        delete ptr2;
        ptr2 = nullptr;
    }

    {
        // (Pg. 227, Figure 7.6)
        // --------------------------------------------
        // Allocate an array of certain type, after use
        // deallocate set ptr to nullptr
        // --------------------------------------------
        int *arr {new int[5]};

        // Dealocate memory & Set pointer to nullptr
        delete[] arr;
        arr = nullptr;

        // --------------------------------------------
        // Allocate & Initialize, after use deallocate,
        // set ptr to nullptr
        // --------------------------------------------
        int *arr2 {new int[] {10, 20, 30}};

        delete arr2;
        arr2 = nullptr;
    }

    {
        // Dyna
    }

    return 0;
}
