#include "api.h"
#include "nlohmann/json.hpp"
#include <cstdio>

using namespace std;
using json = nlohmann::json;

int main() {
    cout << "Reading QR\n";

    cout << "Stage1: Get Data\n";
    string URL;
    URL = "https://hackattic.com/challenges/reading_qr/"
          "problem?access_token=84173d1e3ccdb099";

    optional<string> data = curl_get(URL);
    if (!data) return EXIT_FAILURE;

    auto json_data = json::parse(*data);
    if (!json_data.contains("image_url")) return EXIT_FAILURE;

    string image_url = json_data["image_url"];
    cout << "image_url" << image_url << endl;
    save_image(image_url);

    FILE* image;
    image = fopen("image.png", "w");
    fclose(image);

    cout << "Stage2: Process Image\n";

    return 0;
}
