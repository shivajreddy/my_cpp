#include "api.h"
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

/*
val = z0r/iB5AuLZaXwAA96EGQ1UFvMO2JnNAQHMmtsO8BVU=
base64 encoded

int
unsigned int
short
float
double (probably little endian)
double (big endian)
 */

int main() {
    cout << "Help me unpack\n";

    cout << "Stage1: Get Data\n";
    const char* URL = "https://hackattic.com/challenges/help_me_unpack/"
                      "problem?access_token=84173d1e3ccdb099";
    optional<string> data = get_data(URL);

    if (!data) {
        return EXIT_FAILURE;
    }
    cout << "data: " << *data << endl;

    // string data_str = *data;
    // cout << "data: " << data_str << endl;

    auto json_data = json::parse(*data);
    if (!json_data.contains("bytes")) {
        return EXIT_FAILURE;
    }
    string val = json_data["bytes"];
    cout << "val: " << val << endl;

    return 0;
}
