#include "get_data.h"
#include <curl/curl.h> // library to make GET requests
#include <stdio.h>
#include <string.h>

size_t write_callback(void* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t total = size * nmemb;
    strncat((char*)userdata, ptr, total);
    return total;
}

#define RESP_LEN 10000

const char* BASE_URL = "https://hackattic.com";
const char* ENDPOINT =
    "/challenges/mini_miner/problem?access_token=84173d1e3ccdb099";
const char* API_ENDPOINT = "https://hackattic.com/challenges/mini_miner/"
                           "problem?access_token=84173d1e3ccdb099";

void get_data() {
    CURL* curl;
    CURLcode res;
    char response[RESP_LEN] = { 0 }; // buffer for response

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, API_ENDPOINT);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
            printf("Response:\n%s\n", response);
        else
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}
