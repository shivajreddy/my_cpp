#include "api.h"
#include "nlohmann/json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using json = nlohmann::json;

struct Image {
    int width;
    int height;
    int channels;
    unsigned char* pixels;

    // Built after PREPROCESSING, deleted at deconstructor
    unsigned char* grayscale;
    unsigned char* binary_pixels;

    // Constructor
    Image(int width, int height, int channels, unsigned char* pixels) {
        this->width = width;
        this->height = height;
        this->channels = channels;
        this->pixels = pixels;

        do_preprocessing();
    }
    ~Image() {
        if (grayscale) delete[] grayscale;
        if (binary_pixels) delete[] binary_pixels;
    }

public:
    size_t color_idx(int h, int w) {
        return (size_t)(h * width + w) * channels;
    }

    size_t gray_idx(int h, int w) {
        return (size_t)(h * width + w);
    }

    pair<int, int> coords(size_t pixel_idx) {
        size_t pixel_num = pixel_idx / channels;
        size_t start_h = pixel_num / width;
        size_t start_w = pixel_num % width;
        return { start_h, start_w };
    }

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

    // STAGE 1 : PREPROCESSING
private:
    void do_preprocessing() {
        // 1.1 : Build grayscale
        this->grayscale = new unsigned char[height * width];
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                size_t c_idx = color_idx(h, w);
                size_t g_idx = gray_idx(h, w);
                auto [r, g, b] = rgb(c_idx);
                double intensity = (double)(r + g + b) / 3;
                grayscale[g_idx] = (unsigned char)intensity;
            }
        }
        // 1.2 : Build binary pixels
        this->binary_pixels = new unsigned char[height * width];
        const int WINDOW_SIZE = 15;
        const double THRESHOLD_BIAS = 10.0;
        auto get_threshold = [&](int h, int w) {
            double total = 0.0;
            int count = 0; // valid cells
            int half_win = WINDOW_SIZE / 2;
            for (int curr_h = h - half_win; curr_h <= h + half_win; curr_h++) {
                if (curr_h < 0 || curr_h == height) continue;
                for (int curr_w = w - half_win; curr_w <= w + half_win;
                     curr_w++) {
                    if (curr_w < 0 || curr_w == width) continue;
                    size_t g_idx = gray_idx(curr_h, curr_w);
                    total += grayscale[g_idx];
                    count++;
                }
            }
            double avg = total / count;
            return (double)(avg - THRESHOLD_BIAS);
        };
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                size_t idx = gray_idx(h, w);
                double threshold = get_threshold(h, w);
                binary_pixels[idx] = (grayscale[idx] < threshold) ? 0 : 255;
            }
        }
    }
};

// Read QR code
void read_qrcode() {
    const char* img_path = "/mnt/c/Users/sreddy/Desktop/test1.png"; // white
    // const char* img_path = "/mnt/c/Users/sreddy/Desktop/test2.png"; // blank
    // const char* img_path = "/Users/smpl/Desktop/pix1.png"; // blank
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
    printf("image.grayscale\n");
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            printf("%3d ", (int)image.grayscale[image.gray_idx(h, w)]);
        }
        printf("\n");
    }
    printf("image.binary_pixels\n");
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            printf("%3d ", (int)image.binary_pixels[image.gray_idx(h, w)]);
        }
        printf("\n");
    }

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
