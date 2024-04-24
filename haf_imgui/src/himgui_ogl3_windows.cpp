#include "himgui_ogl3_windows.hpp"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include <Windows.h>

namespace himgui::ogl3w
{
bool InitImp()
{
    bool result{ImGui_ImplOpenGL3_Init()};
    result &= ImGui_ImplWin32_InitForOpenGL(GetActiveWindow());
    return result;
}

}
