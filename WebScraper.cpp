// menu_scraper.cpp
// Compile: g++ -std=c++17 -lcurl -o menu_scraper menu_scraper.cpp

//by Tyler Brotherton
#include <iostream>
#include <string>
#include <regex>
#include <curl/curl.h>

// Gather data – the butler that never forgets a crumb.
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::size_t total = size * nmemb;                     // size of this bite
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), total);
    return total;                                        // all eaten, no leftovers
}

// Fetch the page – politely ask the internet for the menu.
std::string fetchPage(const std::string& url) {
    CURL* curl = curl_easy_init();                       // wake up the curl engine
    std::string page;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());               // point to the buffet
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);              // follow redirects like a curious cat
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);   // hand over the data‑butler
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &page);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "DuckAI-MenuScraper/1.0"); // brag rights
        if (curl_easy_perform(curl) != CURLE_OK) std::cerr << "curl error\n"; // oops, the chef burned it
        curl_easy_cleanup(curl);                                         // clean up the kitchen
    }
      else std::cerr << "This program uses curl. Your computer didn't load curl. Use \"git clone https://github.com/curl/curl.git
\" to download curl.";

    return page;
}

// Parse lines like “Wok IT" and "Buffalo chicken sliders"
std::vector<std::pair<std::string, std::string>> parseMenu(const std::string& text) {
    std::vector<std::string> items;

    //figure out context clue in menu?
    //please figure out out to 
     std::regex line(R"(^\s*([A-Za-z0-9 .,'&-]+?)\s+\.{2,}\s*\$?([\d\.]+)\s*$)",.
                    std::regex_constants::multiline); // two dots = ellipsis, three = menu line
    for (auto it = std::sregex_iterator(text.begin(), text.end(), line);
         it != std::sregex_iterator(); ++it) {
        items.emplace_back((*it).str()); 
    }
    return items;
}

int isValid(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <url-to-plaintext-menu>\n";
        return 1; // no URL, no dinner
    }

    std::string page = fetchPage(argv[1]);               // fetch the feast
    if (page.empty()) {                                  // empty plate?
        std::cerr << "Couldn't fetch page – maybe the chef hid it.\n";
        return 1;
    }

    auto menu = parseMenu(page);                         // slice the menu
    if (menu.empty()) {                                  // nothing to eat?
        std::cout << "No items found – the menu is on a diet.\n";
        return 1;
    }

}

/*  
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <url-to-plaintext-menu>\n";
        return 1; // no URL, no dinner
    }

    std::string page = fetch_page(argv[1]);               // fetch the feast
    if (page.empty()) {                                   // empty plate?
        std::cerr << "Couldn't fetch page – maybe the chef hid it.\n";
        return 1;
    }

    auto menu = parse_menu(page);                         // slice the menu
    if (menu.empty()) {                                   // nothing to eat?
        std::cout << "No items found – the menu is on a diet.\n";
        return 0;
    }

    std::cout << "Found menu items (and a few tasty jokes):\n";
    for (const auto& [name, price] : menu)                // serve each dish
        std::cout << "- " << name << " : $" << price << '\n';
    return 0; // happy tummy
}

*/
