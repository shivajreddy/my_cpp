#include "api.h"
#include "nlohmann/json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using json = nlohmann::json;

// Read QR code
void read_qrcode() {
    const char* img_path = "/Users/smpl/Desktop/test.png"; // has padding
    // const char* img_path = "/Users/smpl/Desktop/test2.png"; // no padding
    // const char* img_path = "/Users/smpl/Desktop/test3.png"; // color

    int width, height, channels;
    // image is a 1D array of pixels
    unsigned char* image = stbi_load(img_path, &width, &height, &channels, 0);
    if (image == nullptr) exit(1); // failed to load image
    printf("Image loaded: Width=%d, Height=%d, Channels=%d\n", width, height,
           channels);

    /*
    h=2 w=2 c=4
    rgba rgba
    */
    // cout << "sizeof(image): " << sizeof(image) << endl;
    // for (auto pixel : image) { cout << pixel << endl; }
    cout << "h*w: " << height * width << endl; // 69696
    for (int h = 0; h < height; h++)
        for (int w = 0; w < width; w++) {
            size_t pixel_idx = (size_t)(h * width + w) * channels;
            // cout << pixel_idx << " : " << image[pixel_idx] << endl;
            int r = image[pixel_idx];
            int g = image[pixel_idx + 1];
            int b = image[pixel_idx + 2];
            if (channels >= 4) {
                int c = image[pixel_idx + 3];
                printf("r:%d g:%d b:%d c:%d\n", r, g, b, c);
            } else {
                printf("r:%d g:%d b:%d\n", r, g, b);
            }
        }

    stbi_image_free(image); // free up the image, closes the fd
}

int main() {
    read_qrcode();
    return 0;

    cout << "Reading QR\n";

    // Get the image url
    cout << "Stage1: Get Data\n";
    string URL;
    URL = "https://hackattic.com/challenges/reading_qr/"
          "problem?access_token=84173d1e3ccdb099";
    optional<string> data = curl_get(URL);
    if (!data) return EXIT_FAILURE;
    auto json_data = json::parse(*data);
    if (!json_data.contains("image_url")) return EXIT_FAILURE;

    // Save the image as png
    string image_url = json_data["image_url"];
    cout << "saving image from image_url: " << image_url << endl;
    save_image(image_url);

    // Process the Image
    cout << "Stage2: Process Image\n";

    // Send the response
    return 0;
}
