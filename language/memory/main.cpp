#include <iostream>
#include <vector>

using namespace std;

void print_array(int *arr, size_t size) {
    for (size_t idx = 0; idx < size; ++idx) {
        cout << arr[idx] << " ";
    }
    cout << "\n";
}

void print_vector(vector<int> &arr) {
    for (auto num : arr) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {

    int buffer[8];
    for (size_t idx = 0; idx < 8; ++idx) {
        buffer[idx] = idx * idx;
    }
    cout << buffer << endl;

    print_array(buffer, 8);

    vector<int> nums = {20, 30, 40, 50};
    print_vector(nums);

    for (size_t i = 0; i < nums.size(); ++i) {
        nums[i] = nums[i] * nums[i];
    }
    print_vector(nums);

    // Dynamically allocated array
    int *dyn_arr = new int[3];

    delete[] dyn_arr;

    cout << dyn_arr[0] << endl;
    cout << dyn_arr[1] << endl;

    return 0;
}
