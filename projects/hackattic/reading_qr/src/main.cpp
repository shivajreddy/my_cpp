#include "api.h"
#include "nlohmann/json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using json = nlohmann::json;

struct Image {
    unsigned char* pixels;
    int width;
    int height;
    int channels;
};

bool is_black(const Image& image, size_t pix_idx) {
    int r = image.pixels[pix_idx], b = image.pixels[pix_idx + 1],
        g = image.pixels[pix_idx + 2];
    return (r == 0 && b == 0 && g == 0);
};

bool is_white(const Image& image, size_t pix_idx) {
    int r = image.pixels[pix_idx], b = image.pixels[pix_idx + 1],
        g = image.pixels[pix_idx + 2];
    return (r == 255 && b == 255 && g == 255);
};

pair<size_t, size_t> top_left_square(const Image& image, size_t idx) {
    size_t pixel_num = idx / image.channels;
    size_t start_h = pixel_num / image.width, start_w = pixel_num / image.width;
    printf("finding coords at start_h:%zu start_w:%zu\n", start_h, start_w);

    int w = start_w;
    for (; w < image.width; w++) {
        size_t pix_idx = (size_t)(start_h * image.width + w) * image.channels;
        if (!is_black(image, pix_idx)) break;
    }
    if (w == image.width) return { -1, -1 };
    return { start_w, --w };
}

// Step 1: Identify the three squares
void identify_squares(const Image& image) {
    // bool top_left = false, top_right = false, bottom_left = false;
    // size_t tl_idx, tr_idx, bl_idx;
    bool top_left = false;
    size_t tl_idx, tl_padding;
    // Finding top-left
    for (int h = 0; h < image.height; h++) {
        if (top_left) break;
        for (int w = 0; w < image.width; w++) {
            size_t pix_idx = (size_t)(h * image.width + w) * image.channels;
            if (is_black(image, pix_idx)) {
                tl_idx = pix_idx;
                tl_padding = w;
                top_left = true;
                break;
            }
        }
    }
    if (top_left) {
        auto res = top_left_square(image, tl_idx);
        cout << res.first << "," << res.second << endl;
    } else {
        cout << "Failed to find topleft\n";
    }
}

// Read QR code
void read_qrcode() {
    const char* img_path = "/Users/smpl/Desktop/pix2.png"; // has padding
    // const char* img_path = "/Users/smpl/Desktop/test.png"; // has padding
    // const char* img_path = "/Users/smpl/Desktop/test2.png"; // no padding
    // const char* img_path = "/Users/smpl/Desktop/test3.png"; // color

    int width, height, channels;
    // image is a 1D array of pixels
    unsigned char* pixels = stbi_load(img_path, &width, &height, &channels, 0);
    if (pixels == nullptr) exit(1); // failed to load image
    Image image = { pixels, width, height, channels };
    printf("Image loaded: W=%d, H=%d, Channels=%d\n", width, height, channels);

    /*
    h=2 w=2 c=4
    rgba rgba
    */
    // cout << "sizeof(image): " << sizeof(image) << endl;
    // for (auto pixel : image) { cout << pixel << endl; }
    // cout << "h*w: " << height * width << endl; // 69696
    int blacks = 0, whites = 0, colors = 0;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            size_t pixel_idx = (size_t)(h * width + w) * channels;
            // cout << pixel_idx << " : " << image[pixel_idx] << endl;
            if (is_black(image, pixel_idx))
                blacks++;
            else if (is_white(image, pixel_idx))
                whites++;
            else
                colors++;
            if (channels >= 4) {
                // int c = image[pixel_idx + 3];
                // printf("r:%d g:%d b:%d c:%d\n", r, g, b, c);
            } else {
                // printf("r:%d g:%d b:%d\n", r, g, b);
            }
        }
    }
    printf("whites:%d blacks:%d colors:%d\n", whites, blacks, colors);

    identify_squares(image);

    stbi_image_free(pixels); // free up the image, closes the fd
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
