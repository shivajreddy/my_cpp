#ifndef PARSE_DATA_H
#define PARSE_DATA_H

#include <nlohmann/json.hpp>
#include <optional>
#include <sstream>
#include <string>

using json = nlohmann::json;

using std::optional;
using std::ostringstream;
using std::pair;
using std::string;
using std::vector;

struct Block {
    optional<int> nonce;
    vector<pair<string, int>> data;
};

struct ApiResponse {
public:
    int difficulty;
    Block block;

public:
    string to_string() {
        ostringstream oss;
        oss << "{";
        oss << "\"difficulty\":" << difficulty << ",";
        oss << "\"block\":{";

        // Serialize block
        oss << "\"data\":[";
        for (size_t i = 0; i < block.data.size(); ++i) {
            const auto& [key, val] = block.data[i];
            oss << "[\"" << key << "\"," << val << "]";
            if (i + 1 < block.data.size()) oss << ",";
        }
        oss << "],";

        if (block.nonce.has_value()) {
            oss << "\"nonce\":" << block.nonce.value();
        } else {
            oss << "\"nonce\":null";
        }

        oss << "},"; // end block

        // oss << "\"raw_val\":\"" << api.raw_val << "\"";
        oss << "}";
        return oss.str();
    }
};

// void process_data(std::string data);
// std::optional<json> process_data(std::string data);
optional<ApiResponse> parse_api_response(string data);

#endif
