#ifndef HAF_IMGUI_INCLUDE_HPP
#define HAF_IMGUI_INCLUDE_HPP

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

#endif
