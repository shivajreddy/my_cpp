#include "process_data.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

using namespace std;

using json = nlohmann::json;

/*
{
    "difficulty" : 13, "block" : {"nonce": null, "data":
[["2416b4918eef8394f1d48 63fa1bfed97", -94],
["297de04d457878e60f051c5a6e699725", 66], ["a32af21a8004 09c5b23ac3ca3f9740dc",
67], ["088f8da652f8393cff1ca8a02cef694f", -51]]}}
*/

inline void from_json(const json& j, pair<string, int>& p) {
    p.first = j.at(0).get<string>();
    p.second = j.at(1).get<int>();
};
inline void from_json(const json& j, Block& b) {
    if (j.contains("nonce") && !j["nonce"].is_null()) {
        b.nonce = j["nonce"].get<int>();
    } else {
        b.nonce = nullopt;
    }
}
inline void from_json(const json& j, ApiResponse& r) {
    r.difficulty = j.at("difficulty").get<int>();
    r.block = j.at("block").get<Block>();
}
/*
 */

optional<ApiResponse> process_data(string data) {
    try {
        auto res = json::parse(data);
        ApiResponse resp = res.get<ApiResponse>();
        return resp;
    }
    catch (json::parse_error& e) {
        cerr << "JSON parse error" << e.what() << "\n";
        return nullopt;
    }
}
