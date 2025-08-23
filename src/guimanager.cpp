#include "guimanager.h"
#include "settingsmanager.h"

#include <windows.h>
#include "misc/cpp/imgui_stdlib.h"
#include <cstring>

void StartUI()
{
    glfwInit();

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    int width  = 500; // GetSystemMetrics(SM_CXSCREEN);
    int height = 400; // GetSystemMetrics(SM_CYSCREEN);

    GLFWwindow* window = glfwCreateWindow(width, height, "Assault Cube Trainer", nullptr, nullptr);
    glfwHideWindow(window);

    glfwMakeContextCurrent(window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiIO& io = ImGui::GetIO();
    //io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    std::string activeKeybind = "None";
    
    bool binding = false;

    Settings settings = LoadSettings();

    
    while (!glfwWindowShouldClose(window))
    {
        bool settingsAltered = false;

        glfwPollEvents();

       

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoBringToFrontOnFocus |
                                 ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Hello", nullptr, flags);


        ImGui::Text("Settings");
        if(!binding || activeKeybind == "None") {
            ImGui::Text("Aimbot Key(%s)", settings.aimbotKey.keyName);
            ImGui::SameLine();
            if(ImGui::Button("Bind Key")) {
                binding = true;
                activeKeybind = "Aimbot";
            }
        }
        else {
            ImGui::Text("Press Key To Bind...");
            Key key = GetKeyToBind();
            if(std::strlen(key.keyName) != 0) {
                binding = false;
                activeKeybind = "None";
                settings.aimbotKey = key;
                settingsAltered = true;
            }
        }
        
        ImGui::End();

        ImGui::Render();

        int display_w, display_h;
       // glfwGetFramebufferSize(window, &display_w, &display_h);
       // glViewport(0,0,display_w,display_h);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // RGBA (last param = alpha)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        glfwSwapBuffers(window);

        if(settingsAltered) {
            SaveSettings(settings);
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}