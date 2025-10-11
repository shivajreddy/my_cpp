#include "api.h"
#include <cstdint>
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

class Base64 {
private:
    // Base64 character set
    static const std::string base64_chars;

    // Helper function to check if a character is base64
    static inline bool is_base64(unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }

public:
    // Encode binary data to base64 string
    static std::string encode(const std::vector<unsigned char>& data) {
        std::string ret;
        int i = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];
        size_t in_len = data.size();
        size_t pos = 0;

        while (in_len--) {
            char_array_3[i++] = data[pos++];

            if (i == 3) {
                // Convert 3 bytes to 4 base64 characters
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                                  ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                                  ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for (i = 0; i < 4; i++) ret += base64_chars[char_array_4[i]];
                i = 0;
            }
        }

        // Handle remaining bytes (padding)
        if (i) {
            for (int j = i; j < 3; j++) char_array_3[j] = '\0';

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                              ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                              ((char_array_3[2] & 0xc0) >> 6);

            for (int j = 0; j < i + 1; j++)
                ret += base64_chars[char_array_4[j]];

            while (i++ < 3) ret += '=';
        }

        return ret;
    }

    // Overload for string input
    static std::string encode(const std::string& input) {
        std::vector<unsigned char> data(input.begin(), input.end());
        return encode(data);
    }

    // Decode base64 string to binary data
    static std::vector<unsigned char>
    decode(const std::string& encoded_string) {
        size_t in_len = encoded_string.size();
        int i = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::vector<unsigned char> ret;

        while (in_len-- && (encoded_string[in_] != '=') &&
               is_base64(encoded_string[in_])) {
            char_array_4[i++] = encoded_string[in_];
            in_++;

            if (i == 4) {
                // Convert each base64 char to its index
                for (i = 0; i < 4; i++)
                    char_array_4[i] = base64_chars.find(char_array_4[i]);

                // Convert 4 base64 characters back to 3 bytes
                char_array_3[0] =
                    (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) +
                                  ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] =
                    ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; i < 3; i++) ret.push_back(char_array_3[i]);
                i = 0;
            }
        }

        // Handle remaining characters
        if (i) {
            for (int j = 0; j < i; j++)
                char_array_4[j] = base64_chars.find(char_array_4[j]);

            char_array_3[0] =
                (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) +
                              ((char_array_4[2] & 0x3c) >> 2);

            for (int j = 0; j < i - 1; j++) ret.push_back(char_array_3[j]);
        }

        return ret;
    }

    // Decode to string (for text data)
    static std::string decode_to_string(const std::string& encoded_string) {
        std::vector<unsigned char> decoded = decode(encoded_string);
        return { decoded.begin(), decoded.end() };
    }
};

// Define the base64 character set
const std::string Base64::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                         "abcdefghijklmnopqrstuvwxyz"
                                         "0123456789+/";

struct Answer {
    int32_t _int;
    uint32_t _uint;
    int16_t _short;
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
    // decode the data
    // c0IOjeK0U7hPggAApeEYQ4F5FUjF4lVAQFXixUgVeYE=
    // how to even unpack it?
    cout << data << endl;
    cout << Base64::decode_to_string(data) << endl;

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
