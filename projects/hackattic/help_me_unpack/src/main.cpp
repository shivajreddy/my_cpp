#include "api.h"
#include "base64.h"
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

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
// Convert a double to big-endian byte order and return as hex string
std::string double_to_big_endian_hex(double value) {
    uint64_t temp;
    std::memcpy(&temp, &value, sizeof(double));

    // Check system endianness
    uint16_t test = 0x1;
    bool is_little_endian = *reinterpret_cast<uint8_t*>(&test) == 0x1;

    if (is_little_endian) {
        // Reverse bytes if system is little-endian
        uint64_t reversed = 0;
        for (int i = 0; i < 8; i++) {
            reversed |= ((temp >> (8 * i)) & 0xFFULL) << (8 * (7 - i));
        }
        temp = reversed;
    }

    // Convert to hex string
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (int i = 7; i >= 0; i--) {
        oss << std::setw(2) << ((temp >> (i * 8)) & 0xFF);
    }

    return oss.str();
}

std::string make_json(int a, unsigned int b, short c, float d, double e,
                      double f_big_endian) {
    std::ostringstream oss;
    oss << std::fixed
        << std::setprecision(6); // control float/double formatting

    oss << "{";
    oss << "\"int\": " << a << ", ";
    oss << "\"uint\": " << b << ", ";
    oss << "\"short\": " << c << ", ";
    oss << "\"float\": " << d << ", ";
    oss << "\"double\": " << e << ", ";
    oss << "\"double_big_endian\": \"" << double_to_big_endian_hex(f_big_endian)
        << "\"";
    oss << "}";

    return oss.str();
}

string get_answer(string encoded_str) {
    // decode the data
    // c0IO jeK0 U7hP ggAA peEY Q4F5 FUjF 4lVA QFXi xUgV eYE=
    cout << "encoded_str: " << encoded_str << endl;
    // z0r / iB5A uLZa XwAA 96EG Q1UF vMO2 JnNA QHMm tsO8 BVU =
    // string s = "QUJD";
    // bitset<24> bs = base64_to_bits(s);
    // cout << base64_to_bits(s) << endl;
    // cout << bits_to_str(bs) << endl;

    string s = "QUJDQUJDQU==";
    s = "z0r/iB5AuLZaXwAA96EGQ1UFvMO2JnNAQHMmtsO8BVU=";
    s = "z0r/";
    string res = "";
    for (size_t i = 0; i < s.size(); i += 4) {
        auto sub_s = s.substr(i, 4);
        bitset<24> bs = base64_to_bits(sub_s);
        res += bits_to_str(bs);
    }
    cout << "decoded: " << res << endl;

    string json_str = make_json(1, 2, 3, 4.4, 5.5, 6.6);

    return json_str;
};

int main() {
    cout << "Help me unpack\n";

    cout << "Stage1: Get Data\n";
    const char* URL = "https://hackattic.com/challenges/help_me_unpack/"
                      "problem?access_token=84173d1e3ccdb099";

    optional<string> data = get_data(URL);
    if (!data) return EXIT_FAILURE;

    auto json_data = json::parse(*data);
    if (!json_data.contains("bytes")) return EXIT_FAILURE;

    cout << "Stage2: Decode string\n";
    string json_str = get_answer(json_data["bytes"]);

    cout << "Stage 3: Post Data\n";
    const char* POST_URL = "https://hackattic.com/challenges/help_me_unpack/"
                           "solve?access_token=84173d1e3ccdb099";
    api_post_data(POST_URL, json_str);

    return 0;
}
