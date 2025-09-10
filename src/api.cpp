#include "api.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "incs/nlohmann/json.hpp"
using json = nlohmann::json;
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void getLink() {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos/1");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "Hata: " << curl_easy_strerror(res) << std::endl;
        else {
            json j = json::parse(response);
            std::cout << "UserId: " << j["userId"] << std::endl;
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
};
bool Login(std::string username, std::string password) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    json j;
    j["username"] = username;
    j["password"] = password;
    std::string jsonData = j.dump(); // string'e çevir

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Headers: JSON gönderiyoruz
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/api.php"); // API URL
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // İsteği gönder
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "Curl hatası: " << curl_easy_strerror(res) << std::endl;
        else
            printf("Response: %s\n", response.c_str());
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    json respp = json::parse(response);
    curl_global_cleanup();
    return respp["success"];
};