#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Helper to fetch JSON from Wikipedia
bool fetch_wikipedia_json(const std::string& title, std::string& out_json) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    // Encode spaces and special characters
    char* encoded = curl_easy_escape(curl, title.c_str(), static_cast<int>(title.length()));
    std::string url = "https://en.wikipedia.org/api/rest_v1/page/summary/";
    url += encoded;
    curl_free(encoded);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out_json);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "DuckAI/1.0 (https://duckduckgo.com)");

    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) && (http_code == 200);
}

// Extract first sentence from the "extract" field
std::string get_first_sentence(const std::string& extract) {
    size_t pos = extract.find('.');
    if (pos != std::string::npos) {
        return extract.substr(0, pos + 1);
    }
    return extract; // fallback: whole text
}

int main() {
    std::cout << "Enter Wikipedia article title (or full URL): ";
    std::string input;
    std::getline(std::cin, input);

    // If a full URL is given, keep only the title part after the last '/'
    if (input.rfind("https://", 0) == 0) {
        size_t slash = input.find_last_of('/');
        if (slash != std::string::npos && slash + 1 < input.size())
            input = input.substr(slash + 1);
    }

    std::string json_data;
    if (!fetch_wikipedia_json(input, json_data)) {
        std::cerr << "Error: Could not retrieve article or article does not exist.\n";
        return 1;
    }

    try {
        json j = json::parse(json_data);
        if (!j.contains("extract")) {
            std::cerr << "Error: Article has no summary.\n";
            return 1;
        }
        std::string top_string = get_first_sentence(j["extract"].get<std::string>());
        std::cout << "Top sentence: " << top_string << "\n";
    } catch (const json::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
