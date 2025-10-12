#ifndef BASE64_H
#define BASE64_H

#include <bitset>
#include <stdlib.h>
#include <string>

using std::bitset;
using std::string;
using std::to_string;

size_t base64_val(unsigned char c);
bitset<24> base64_to_bits(const string& s);
string bits_to_str(bitset<24> bits);

#endif
