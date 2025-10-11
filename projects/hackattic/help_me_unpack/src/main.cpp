#include "api.h"
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

/*
val = z0r/iB5AuLZaXwAA96EGQ1UFvMO2JnNAQHMmtsO8BVU=
base64 encoded

32bit platform
int             : 4bytes
unsigned int    : 4bytes
short           : 2?
float           : 8?
double (probably little endian) : 8?
double (big endian)             : 8?
*/

struct Answer {
    int _int;
    unsigned int _uint;
    short _short;
    float _float;
    double _double;
    double _double2;

    void print() const {
        cout << _int << endl;
        cout << _uint << endl;
        cout << _short << endl;
        cout << _float << endl;
        cout << _double << endl;
        cout << _double2 << endl;
    }
};

Answer get_answer(string data) {
    Answer res;
    res._int = 1;
    res._uint = 1;
    res._short = 1;
    res._float = 1;
    res._double = 1;
    res._double2 = 1;
    return res;
};

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

    Answer ans = get_answer(val);
    ans.print();

    return 0;
}
