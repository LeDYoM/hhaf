#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include <Windows.h>
#include "himgui_ogl3_windows.hpp"

namespace
{
constinit bool himgui_initialized{false};
}

namespace himgui
{
void init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    // Setup Platform/Renderer bindings
    ogl3w::InitImp();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    himgui_initialized = true;
}

void update()
{
    ImGui::Text("abc");
    ImGui::Text("abcd");
    ImGui::Text("abce");
}

void initFrame()
{
    ogl3w::NewFrameImp();
    ImGui::NewFrame();
}

void initWindow()
{
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({400, 400});
    ImGui::Begin("Demo window");
}

void finishWindow()
{
    ImGui::End();
}

void finishFrame()
{
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

void addMessage(char const* const message)
{
    if (himgui_initialized)
    {
        ImGui::Text(message);
    }
}

}  // namespace himgui
