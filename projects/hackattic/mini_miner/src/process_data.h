#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <nlohmann/json.hpp>
#include <optional>
#include <string>

using json = nlohmann::json;

using std::optional;
using std::pair;
using std::string;
using std::vector;

struct Block {
    optional<int> nonce;
    vector<pair<string, int>> data;
};

struct ApiResponse {
    int difficulty;
    Block block;
};

// void process_data(std::string data);
// std::optional<json> process_data(std::string data);
optional<ApiResponse> process_data(string data);

#endif
