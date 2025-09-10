#pragma once
#include <string>
void getLink();
bool Login(std::string username, std::string password);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
