#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include <Windows.h>

namespace himgui
{
void init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    // Setup Platform/Renderer bindings
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplWin32_InitForOpenGL(GetActiveWindow());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize({400, 400});
    ImGui::Begin("Demo window");
    ImGui::Text("abc");
    ImGui::Text("abcd");
    ImGui::Text("abce");
    ImGui::End();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

}  // namespace himgui
