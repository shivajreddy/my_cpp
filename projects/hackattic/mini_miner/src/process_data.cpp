#include "process_data.h"
#include "parse_data.h"
#include <iostream>
#include <sstream>

#include <openssl/sha.h>

using namespace std;

string sha256(string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(),
           hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return oss.str();
}

void process_data(ApiResponse res) {
    // cout << "given rawval: " << res.raw_val << endl;
    // cout << "sha256()=" << sha256(res.raw_val) << endl;
    string sample_input = R"({"data":[],"nonce":45})";
    cout << "sample_input: " << sample_input << endl;
    cout << "sha256(sample_input):" << sha256(sample_input) << endl;

    auto samp_data = parse_api_response(sample_input);
    // auto samp_data_str = samp_data->to_string();
    // cout << "sample_data: " << samp_data_str << endl;
    // cout << "sha256(sample_data):" << sha256(samp_data_str) << endl;
}
