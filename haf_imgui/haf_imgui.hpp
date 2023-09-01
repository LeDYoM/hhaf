#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include <Windows.h>

namespace himgui
{
void init();
void initFrame();
void initWindow();
void finishWindow();
void finishFrame();
void update();
void shutdown();
void addMessage(char const * const message);

}  // namespace himgui