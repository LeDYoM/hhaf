#include "himgui_glfw.hpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace himgui::glfw
{
bool InitImp()
{
//    ImGui_ImplGlfw_InitForOpenGL();
//    bool result{ImGui_ImplOpenGL3_Init()};
//    result &= ImGui_ImplWin32_InitForOpenGL(GetActiveWindow());
//    return result;
    return true;
}

void NewFrameImp()
{
}

void FinishFrameImp()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ShutDownImp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

}  // namespace himgui::glfw
