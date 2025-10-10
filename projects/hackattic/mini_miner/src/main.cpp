// system includes
#include <cstdlib>
#include <iostream>
#include <optional>

// project includes
#include "get_data.h"
#include "process_data.h"

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
    auto data = get_data();
    if (!data) { // failed to GET data
        return EXIT_FAILURE;
    }
    cout << *data << "\n";

    cout << "Stage2: Process Data\n";
    auto processed_data = process_data(*data);
    if (!processed_data) {
        return EXIT_FAILURE;
    }

    return 0;
}
