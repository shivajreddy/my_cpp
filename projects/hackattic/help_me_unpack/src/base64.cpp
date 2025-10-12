#include "base64.h"

size_t base64_val(unsigned char c) {
    /*
    ----------------------
    A–Z →  0–25
    a–z →  26–51
    0–9 →  52–61
    +   →  62
    /   →  63
    ----------------------
    */
    if ('A' <= c && c <= 'Z') return c - 'A';           // 0-25
    if ('a' <= c && c <= 'z') return c - 'a' + 26;      // 26-51
    if ('0' <= c && c <= '9') return c - '0' + 26 + 26; // 51-61
    if (c == '+') return 62;
    if (c == '/') return 63;
    throw std::invalid_argument("Invalid Base64 Character");
}

bitset<24> base64_to_bits(const string& s) {
    if (s.size() < 4) throw std::invalid_argument("There should be 4 chars");

    bitset<24> final_res;
    // convert every 4 chars into 24bits
    for (size_t i = 0; i < s.size(); i = i + 4) {
        bitset<24> res;
        // unsigned char c1 = s[i], c2 = s[i + 1], c3 = s[i + 2], c4 = s[i + 3];
        unsigned char arr[4] = {
            static_cast<unsigned char>(s[i + 0]),
            static_cast<unsigned char>(s[i + 1]),
            static_cast<unsigned char>(s[i + 2]),
            static_cast<unsigned char>(s[i + 3]),
        };
        for (size_t i = 0; i < 4; i++) {
            int val;
            val = arr[i] == '=' ? 0 : base64_val(arr[i]);
            for (int j = 0; j < 6; j++) {
                bool bit = (val >> (5 - j)) & 1; // MSB first
                res[24 - (i * 6 + j) - 1] = bit;
            }
        }
        final_res = res;
    }
    return final_res;
}

// string bits_to_str(const bitset<24>& bits) {
string bits_to_str(bitset<24> bits) {
    string res;
    for (int idx = 0; idx < 24; idx += 8) {
        bitset<8> bs;
        for (int i = 0; i < 8; i++) bs[7 - i] = bits[23 - (idx + i)];
        unsigned long val = bs.to_ullong();
        // res += static_cast<char>(val);
        res += to_string(val);
        // res.push_back(static_cast<char>(val));
    }
    return res;
}
