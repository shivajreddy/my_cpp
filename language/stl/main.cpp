#include <iostream>
#include <map>
#include <string>

using namespace std;

void mutate_array(int arr[]) {}

int main() {
    // /*
    // Create a map where the key and value are both integers
    std::map<int, string> hm = {
        {10, "a"},
        {20, "b"},
        {30, "c"},

    };

    // Iterate over the map using structured bindings (C++17 and above)
    cout << "{\n";
    for (auto &[k, v] : hm) {
        std::cout << "  " << k << " : " << v << std::endl;
    }
    cout << "}\n";
    // */

    int x = 20;
    const int *p1 = &x;
    cout << *p1 << endl;

    int y = 30;
    p1 = &y;
    cout << *p1 << endl;

    return 0;
}
