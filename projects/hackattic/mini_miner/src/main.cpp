// system includes
#include <iostream>

// project includes
#include "get_data.h"

using namespace std;

/*
1. Connect to the problem endpoint
   GET /challenges/mini_miner/problem?access_token=84173d1e3ccdb099
2. Read the JSON output
3.
*/

int main() {
    cout << "Mini Miner\n";

    cout << "Stage1: Getting Data\n";
    string* res = get_data();
    if (res == nullptr) { // failed to GET data
        return EXIT_FAILURE;
    }
    cout << *res << "\n";

    cout << "Stage2: Process Data\n";

    return 0;
}
