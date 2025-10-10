#include "get_data.h"
#include <curl/curl.h> // library to make GET requests
#include <iostream>
#include <string>

#define RESP_LEN 10000

using std::string;

const char* API_ENDPOINT = "https://hackattic.com/challenges/mini_miner/"
                           "problem?access_token=84173d1e3ccdb099";

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    auto* str = static_cast<string*>(userp);
    str->append(static_cast<char*>(contents), total_size);
    return total_size;
}

string* get_data() {
    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        std::cerr << "Failed to initialize CURL\n";
        return nullptr;
    }

    string response;

    curl_easy_setopt(curl, CURLOPT_URL, API_ENDPOINT);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        return nullptr;
    }

    // Success
    // std::cout << "Response:\n" << response << "\n";
    curl_easy_cleanup(curl);
    return new string(response); // success
}
