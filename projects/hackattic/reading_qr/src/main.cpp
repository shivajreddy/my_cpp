#include "api.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

int main() {
    cout << "Reading QR\n";

    cout << "Stage1: Get Data\n";
    const char* URL = "https://hackattic.com/challenges/help_me_unpack/"
                      "problem?access_token=84173d1e3ccdb099";

    optional<string> data = get_data(URL);
    if (!data) return EXIT_FAILURE;

    auto json_data = json::parse(*data);
    if (!json_data.contains("bytes")) return EXIT_FAILURE;

    cout << "Stage2: \n";

    return 0;
}
