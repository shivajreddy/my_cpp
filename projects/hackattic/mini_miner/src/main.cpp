// system includes
#include <cstdlib>
#include <iostream>
#include <optional>

// project includes
#include "get_data.h"
#include "parse_data.h"
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
    auto raw = get_data();
    if (!raw) { // failed to GET data
        return EXIT_FAILURE;
    }
    cout << *raw << "\n";

    cout << "Stage2: Parse Data\n";
    auto data = parse_api_response(*raw);
    if (!data) {
        return EXIT_FAILURE;
    }
    // cout << data->difficulty << endl;
    // cout << data->block.data[0].first << endl;

    cout << "Stage3: Process Data\n";
    process_data(*data);
    return 0;
}
