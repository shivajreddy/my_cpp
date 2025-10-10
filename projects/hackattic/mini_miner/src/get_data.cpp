#include "get_data.h"
#include <curl/curl.h> // library to make GET requests
#include <iostream>
#include <optional>
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

std::optional<string> get_data() {
    // Initalize CURL object
    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        std::cerr << "Failed to initialize curl\n";
        return std::nullopt;
    }

    string response; // save the response to this string

    // Set curl options: url, callback fn, location to save response
    curl_easy_setopt(curl, CURLOPT_URL, API_ENDPOINT);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the curl operation
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // GET Failed
    if (res != CURLE_OK) {
        std::cerr << "GET request failed\n";
        return std::nullopt;
    };

    // GET 200 OK
    return response;
}
