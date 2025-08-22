#include "guimanager.h"
#include <windows.h>

void StartUI()
{
    glfwInit();

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    int width  = 500; // GetSystemMetrics(SM_CXSCREEN);
    int height = 400; // GetSystemMetrics(SM_CYSCREEN);

    GLFWwindow* window = glfwCreateWindow(width, height, "Minimal ImGui", nullptr, nullptr);
    glfwHideWindow(window);

    glfwMakeContextCurrent(window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

       

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoBringToFrontOnFocus |
                                 ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Hello", nullptr, flags);
        ImGui::Text("Minimal boilerplate!");
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
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}