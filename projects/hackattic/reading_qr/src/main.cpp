#include "api.h"
#include "nlohmann/json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using json = nlohmann::json;

struct Image {
    unsigned char* pixels;
    unsigned char* grayscale;
    int width;
    int height;
    int channels;

    // Constructor
    Image(int width, int height, int channels, unsigned char* pixels) {
        this->width = width;
        this->height = height;
        this->channels = channels;
        this->pixels = pixels;
        build_grayscale();
    }
    ~Image() {
        if (grayscale) delete[] grayscale;
    }

    // STAGE 1 : PREPROCESSING
    void build_grayscale() {
        unsigned char* res = new unsigned char[width * height];
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                int color_idx = pix_idx(h, w);
                int gray_idx = h * width + w;
                // int intensity = is_black(color_idx) ? 1 : 0;
                auto [r, g, b] = rgb(color_idx);
                double intensity = (double)(r + g + b) / 3;
                res[gray_idx] = (unsigned char)intensity;
            }
        }
        this->grayscale = res;
    }

    size_t pix_idx(int h, int w) {
        return (size_t)(h * width + w) * channels;
    }
    pair<int, int> coords(size_t pixel_idx) {
        size_t pixel_num = pixel_idx / channels;
        size_t start_h = pixel_num / width;
        size_t start_w = pixel_num % width;
        return { start_h, start_w };
    }
    // tuple<int, int, int> rgb(size_t pix_idx) {
    array<int, 3> rgb(size_t pix_idx) {
        return { pixels[pix_idx], pixels[pix_idx + 1], pixels[pix_idx + 2] };
    }

    bool is_transparent(size_t pix_idx) {
        if (this->channels < 4) return false;
        return this->pixels[pix_idx + 3] == 0;
    }

    bool is_black(size_t pix_idx) {
        if (is_transparent(pix_idx)) return false;
        auto [r, g, b] = rgb(pix_idx);
        return (r == 0 && g == 0 && b == 0);
    };

    bool is_white(size_t pix_idx) {
        if (is_transparent(pix_idx)) return false;
        auto [r, g, b] = rgb(pix_idx);
        return (r == 255 && g == 255 && b == 255);
    };
};

// STAGE 2: Structural analysis (find the QR pattern)
void find_qr_pattern(Image* image) {
    // start with a length = min(h,w) / 3, and keep reducing length to 1
    // each stage, if image has 3 squares of this length
    // then further verify the three squares
    // then get the module(block) size from one of the square

<<<<<<< HEAD
    int h = 1, w = 1;

    for (; h < image->height & w < image->width; h++, w++) {
        // h = ;
        // w = ;
=======
    int start_h = 1,
        start_w = 1; // for now i know where the first square starts
    int h = start_h, w = start_w;
    bool valid_right_pix = true, valid_down_pix = true;
    while (true) {
        if (!valid_right_pix || !valid_down_pix) break;
        if (h == image->height) break;
        if (w == image->width) break;
        size_t right_pixel = image->pix_idx(start_h, w);
        (!image->is_black(right_pixel)) ? valid_right_pix = false : w++;
        size_t down_pixel = image->pix_idx(h, start_w);
        (!image->is_black(down_pixel)) ? valid_down_pix = false : h++;
>>>>>>> refs/remotes/origin/main
    }

    if (!valid_down_pix) h--;
    if (!valid_right_pix) w--;
}

// Step 1: Identify the three squares
void identify_squares(Image& image) {
    // bool top_left = false, top_right = false, bottom_left = false;
    // size_t tl_idx, tr_idx, bl_idx;
    bool top_left = false;
    size_t tl_idx;
    // Finding top-left
    for (int h = 0; h < image.height; h++) {
        if (top_left) break;
        for (int w = 0; w < image.width; w++) {
            size_t pix_idx = (size_t)(h * image.width + w) * image.channels;
            if (image.is_black(pix_idx)) {
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
        size_t pix_idx = image.pix_idx(start_h, w);
        if (!image.is_black(pix_idx)) break;
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
    // const char* img_path = "/mnt/c/Users/sreddy/Desktop/test2.png"; // blank
    const char* img_path = "/Users/smpl/Desktop/pix1.png"; // blank
    // const char* img_path = "/Users/smpl/Desktop/pix2.png"; // white
    // const char* img_path = "/Users/smpl/Desktop/test.png"; // has padding
    // const char* img_path = "/Users/smpl/Desktop/test2.png"; // no padding
    // const char* img_path = "/Users/smpl/Desktop/test3.png"; // color

    int width, height, channels;
    unsigned char* pixels = stbi_load(img_path, &width, &height, &channels, 0);
    if (pixels == nullptr) {
        printf("Failed to load image");
        exit(1);
    }
    Image image = Image(width, height, channels, pixels);
    printf("Image loaded: W=%d, H=%d, Channels=%d\n", width, height, channels);

    // identify_squares(image);

    // print grayscale
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            cout << (int)image.grayscale[h * width + w] << " ";
        }
        cout << endl;
    }

    /*
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
    */

    /*
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
    */

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
