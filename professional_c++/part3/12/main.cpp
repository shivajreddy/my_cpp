#include <iostream>
#include <memory>

template <typename T> void print(T inp, bool is_newline = true)
{
    if (!is_newline) {
        std::cout << inp << " ";
    } else {
        std::cout << inp << std::endl;
    }
}

template <typename T> void print_array(const T arr[], int size)
{
    for (int i = 0; i < size; i++)
        print(arr[i], false);
    print("");
}

template <int N> void Array()
{
    // Create an array
    int arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = i + 10;
    }
    // Print the array
    print_array(arr, N);
}

class GamePiece
{
public:
    virtual ~GamePiece() = default;
    virtual std::unique_ptr<GamePiece> clone() const = 0;
};

int main()
{
    int sample[] = { 10, 20, 30 };
    print_array(sample, 3);

    char sample2[] = { 97, 98, 99 };
    print_array(sample2, 3);

    Array<10>();

    return 0;
}
