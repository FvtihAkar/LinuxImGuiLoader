#include "imgui.h"
#include <string>
#include <vector>
#include "api.h"
#include "globals.h"
#include "incs/imgui/imgui.h"
#include "inject.cpp"
static bool triedLogin = false;
bool isSuccess = false;
std::string username = "";
std::string password = "";
static int currentIndex = 0;
std::vector<std::string> options = {"CS2", "VALORANT", "RUST"};
void LoginScreen() {
    ImGui::Begin("Hello, world!", nullptr,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);        
    ImGui::Dummy(ImVec2(5.0f, 0.0f));
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize("Enter Username").x);
    ImGui::TextColored({1.0f,1.0f,1.0f,0.8f}, "Enter Username");    
    ImGui::Dummy(ImVec2(5.0f, 0.0f));             
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 100.0f - 20.0f);
    ImGui::InputText("##EnterUsername",&username,ImGuiInputTextFlags_None);
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize("Enter Password").x);
    ImGui::TextColored({1.0f,1.0f,1.0f,0.8f}, "Enter Password");  
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 100.0f - 20.0f);
    ImGui::InputText("##EnterPassword",&password,ImGuiInputTextFlags_Password);
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize("Submit").x - 10.0f);
    if(ImGui::Button("Submit",{ImGui::CalcTextSize("Enter Password").x,35})) {
        isSuccess = Login(username,password);
        triedLogin = true;
    }
    if(triedLogin) {
        if (!isSuccess) {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Wrong Details!");
        }
        else {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Successfully Logged in!");
            activeWindow = 1;
        }
    }
    ImGui::End();
}
void LoaderScreen() {
    ImGui::Begin("Loader!", nullptr,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);        
    
    
    if (ImGui::BeginCombo("Select Cheat", options[currentIndex].c_str()))
    {
        
        for (int i = 0; i < options.size(); i++)
        {
            bool isSelected = (currentIndex == i);
            if (ImGui::Selectable(options[i].c_str(), isSelected))
                currentIndex = i;
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    if(ImGui::Button("Load!",{350,30})) {
        std::string target = "target";
        std::string soPath = "/home/fatih/Desktop/projects/imag/libhello.so";

        GDBInjector injector(target, soPath);
        if (!injector.inject()) {
            std::cerr << "[!] Injection failed.\n";
        }
    }
    ImGui::End();
}