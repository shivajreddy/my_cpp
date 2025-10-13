#include "api.h"
#include "nlohmann/json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using json = nlohmann::json;

struct Image {
public:
    unsigned char* pixels;
    int width;
    int height;
    int channels;

public:
    size_t pix_idx(int h, int w) {
        return (size_t)(h * width + w) + channels;
    }
    pair<int, int> coords(size_t pixel_idx) {
        size_t pixel_num = pixel_idx / channels;
        size_t start_h = pixel_num / width, start_w = pixel_num / width;
        return { start_h, start_w };
    }
    // tuple<int, int, int> rgb(size_t pix_idx) {
    array<int, 3> rgb(size_t pix_idx) {
        return { pixels[pix_idx], pixels[pix_idx + 1], pixels[pix_idx + 2] };
    }
};

bool is_transparent(const Image& image, size_t pix_idx) {
    if (image.channels < 4) return false;
    return image.pixels[pix_idx + 3] == 0;
}

bool is_black(const Image& image, size_t pix_idx) {
    if (is_transparent(image, pix_idx)) return false;
    int r = image.pixels[pix_idx], g = image.pixels[pix_idx + 1],
        b = image.pixels[pix_idx + 2];
    return (r == 0 && g == 0 && b == 0);
};

bool is_white(const Image& image, size_t pix_idx) {
    if (is_transparent(image, pix_idx)) return false;
    int r = image.pixels[pix_idx], g = image.pixels[pix_idx + 1],
        b = image.pixels[pix_idx + 2];
    return (r == 255 && g == 255 && b == 255);
};

// STAGE 1 : PREPROCESSING
void pre_process(Image* image) {
    // Grayyscale conversion
    for (int h = 0; h < image->height; h++) {
        for (int w = 0; w < image->width; w++) {
            size_t idx = image->pix_idx(h, w);
            auto [r, g, b] = image->rgb(idx);
            // double intensity = 0.299 * r + 0.587 * g + 0.114 * b;
            double intensity = (double)(r + g + b) / 3;
        }
    }
}

// Step 1: Identify the three squares
void identify_squares(const Image& image) {
    // bool top_left = false, top_right = false, bottom_left = false;
    // size_t tl_idx, tr_idx, bl_idx;
    bool top_left = false;
    size_t tl_idx;
    // Finding top-left
    for (int h = 0; h < image.height; h++) {
        if (top_left) break;
        for (int w = 0; w < image.width; w++) {
            size_t pix_idx = (size_t)(h * image.width + w) * image.channels;
            if (is_black(image, pix_idx)) {
                tl_idx = pix_idx;
                top_left = true;
                break;
            }
        }
    }

    if (!top_left) {
        cout << "Failed to find topleft\n";
        return;
    }
    size_t idx = tl_idx;
    size_t pixel_num = idx / image.channels;
    size_t start_h = pixel_num / image.width, start_w = pixel_num / image.width;
    printf("finding coords at start_h:%zu start_w:%zu\n", start_h, start_w);

    int w = start_w;
    for (; w < image.width; w++) {
        size_t pix_idx = (size_t)(start_h * image.width + w) * image.channels;
        if (!is_black(image, pix_idx)) break;
    }
    pair<size_t, size_t> res;
    if (w == image.width)
        res = { -1, -1 };
    else
        res = { start_w, --w };
    cout << res.first << "," << res.second << endl;
}

// Read QR code
void read_qrcode() {
    // const char* img_path = "/mnt/c/Users/sreddy/Desktop/test1.png"; // white
    // bg
    const char* img_path = "/mnt/c/Users/sreddy/Desktop/test2.png"; // blank
    // bg const char* img_path = "/Users/smpl/Desktop/pix2.png"; // has padding
    // const char* img_path = "/Users/smpl/Desktop/test.png"; // has padding
    // const char* img_path = "/Users/smpl/Desktop/test2.png"; // no padding
    // const char* img_path = "/Users/smpl/Desktop/test3.png"; // color

    int width, height, channels;
    // image is a 1D array of pixels
    unsigned char* pixels = stbi_load(img_path, &width, &height, &channels, 0);
    if (pixels == nullptr) {
        printf("Failed to load image");
        exit(1);
    } // failed to load image
    Image image = { pixels, width, height, channels };
    printf("Image loaded: W=%d, H=%d, Channels=%d\n", width, height, channels);

    { //
        printf("testing start----------------\n");
        int h = 1;
        int w = 0;
        size_t pix_idx;
        pix_idx = (size_t)(h * width + w) + channels;
        printf("ch:%d\n", image.pixels[pix_idx + 3]);

        w = 1;
        pix_idx = (size_t)(h * width + w) + channels;
        printf("ch:%d\n", image.pixels[pix_idx + 3]);

        printf("Counting the no.of pixels with 0alpha & 255alpha\n");
        int transparent = 0, visible = 0;
        for (int h = 0; h < image.height; h++) {
            for (int w = 0; w < image.width; w++) {
                size_t pix_idx = (size_t)(h * width + w) * image.channels;
                if (image.pixels[pix_idx + 3] == 0) transparent++;
                if (image.pixels[pix_idx + 3] == 255) visible++;
            }
        }
        printf("transparent:%d visible:%d\n", transparent, visible);

        printf("testing end----------------\n");
    }

    /*
    h=2 w=2 c=4
    rgba rgba
    */
    // cout << "sizeof(image): " << sizeof(image) << endl;
    // for (auto pixel : image) { cout << pixel << endl; }
    // cout << "h*w: " << height * width << endl; // 69696
    int blacks = 0, whites = 0, colors = 0;
    int transparent = 0, opaque = 0;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            size_t pixel_idx = (size_t)(h * width + w) * channels;
            // cout << pixel_idx << " : " << image[pixel_idx] << endl;
            if (is_transparent(image, pixel_idx))
                transparent++;
            else {
                opaque++;
                if (is_black(image, pixel_idx))
                    blacks++;
                else if (is_white(image, pixel_idx))
                    whites++;
                else
                    colors++;
            }
        }
    }
    printf("whites:%d blacks:%d colors:%d\n", whites, blacks, colors);
    printf("transparent:%d opaque:%d\n", transparent, opaque);

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
