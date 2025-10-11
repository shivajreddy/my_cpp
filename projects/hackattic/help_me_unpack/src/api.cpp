#include "api.h"
#include <curl/curl.h>
#include <optional>

using std::optional;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    auto* str = static_cast<string*>(userp);
    str->append(static_cast<char*>(contents), total_size);
    return total_size;
}

optional<string> get_data(const char* URL) {
    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        return std::nullopt;
    }

    string response;

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode curl_code = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (curl_code != CURLE_OK) {
        return std::nullopt;
    }

    return response;
}

void post_response() {
}
