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
short           : 2
float           : 8?
double (probably little endian) : 8?
double (big endian)             : 8?
*/

size_t get_decoded_size(const string& encoded_str) {
    if (encoded_str.empty()) return 0;
    size_t len = encoded_str.length();
    size_t padding = 0;
    if (encoded_str[len - 1] == '=') padding++;
    if (len > 1 && encoded_str[len - 2] == '=') padding++;
    return (len / 4) * 3 - padding;
}

vector<uint8_t> base64_decode(const string& encoded_str) {
    size_t decoded_size = get_decoded_size(encoded_str);
    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "0123456789+/";
    std::vector<uint8_t> decoded;
    decoded.reserve(decoded_size);
    std::vector<int> T(256, -1);
    // Create lookup table
    for (int i = 0; i < 64; i++) T[base64_chars[i]] = i;
    int val = 0, valb = -8;
    for (uint8_t c : encoded_str) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            decoded.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }
    return decoded;
}

// Helper to reverse bytes for endianness conversion
template <typename T> T reverse_endian(const T& value) {
    T result;
    const uint8_t* src = reinterpret_cast<const uint8_t*>(&value);
    uint8_t* dst = reinterpret_cast<uint8_t*>(&result);
    for (size_t i = 0; i < sizeof(T); i++) {
        dst[i] = src[sizeof(T) - 1 - i];
    }
    return result;
}

// Read a value of type T from the decoded bytes at offset
template <typename T>
T read_value(const vector<uint8_t>& data, size_t offset = 0) {
    if (offset + sizeof(T) > data.size()) {
        throw out_of_range("Not enough bytes to read value");
    }

    T value;
    memcpy(&value, data.data() + offset, sizeof(T));
    return value;
}

// Read a big-endian value and convert to native endianness
template <typename T>
T read_big_endian(const vector<uint8_t>& data, size_t offset = 0) {
    T value = read_value<T>(data, offset);

    // Check if system is little-endian (most common)
    uint16_t test = 0x0001;
    bool is_little_endian = (*reinterpret_cast<uint8_t*>(&test) == 0x01);

    if (is_little_endian) {
        return reverse_endian(value);
    }
    return value;
}

string unpack_bytes_str(string encoded_str) {
    vector<uint8_t> bytes = base64_decode(encoded_str);
    // for (uint8_t byte : bytes) cout << (int)byte << " ";
    // cout << endl;
    int a = read_value<int>(bytes, 0);
    int b = read_value<int>(bytes, 4);
    int c = read_value<short>(bytes, 8);
    int d = read_value<float>(bytes, 10);
    int e = read_value<double>(bytes, 14);      // little-endian
    int f = read_big_endian<double>(bytes, 22); // big-endian

    auto make_json = [&](int a, unsigned int b, short c, float d, double e,
                         double f) {
        std::ostringstream oss;
        oss << std::fixed
            << std::setprecision(6); // control float/double formatting

        oss << "{";
        oss << "\"int\": " << a << ", ";
        oss << "\"uint\": " << b << ", ";
        oss << "\"short\": " << c << ", ";
        oss << "\"float\": " << d << ", ";
        oss << "\"double\": " << e << ", ";
        oss << "\"big_endian_double\": \"" << f << "\"";
        oss << "}";

        return oss.str();
    };
    // string json_str = make_json(1, 2, 3, 4.4, 5.5, 6.6);
    string json_str = make_json(a, b, c, d, e, f);
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
    string json_str = unpack_bytes_str(json_data["bytes"]);
    cout << "json_str: " << json_str << endl;

    cout << "Stage 3: Post Data\n";
    const char* POST_URL = "https://hackattic.com/challenges/help_me_unpack/"
                           "solve?access_token=84173d1e3ccdb099";
    api_post_data(POST_URL, json_str);

    return 0;
}
