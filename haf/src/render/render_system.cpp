#include "render_system.hpp"
#include "render_target.hpp"
#include <hlog/include/hlog.hpp>
#include <hogl/include/render_system_functions.hpp>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include <Windows.h>

using namespace haf::core;
using namespace haf::render;

namespace haf::sys
{
void RenderSystem::initialize(bool const enableDebug)
{
    m_initialized = ogl::initOGL();
    LogAsserter::log_assert(m_initialized == true);
    ogl::setDebug(enableDebug);
    ogl::setDefaultRenderState();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    // Setup Platform/Renderer bindings
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplWin32_Init(GetActiveWindow());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void RenderSystem::update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    ImGui::Begin("Demo window");
    if (ImGui::Button("Hello world!"))
    {
        ImGui::Text("abc");
    }
    ImGui::End();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

sptr<RenderTarget> const& RenderSystem::currentRenderTarget() const
{
    return render_target_;
}

SharedDataManager& RenderSystem::sharedDataManager() noexcept
{
    return m_shared_data_manager;
}

SharedDataManager const& RenderSystem::sharedDataManager() const noexcept
{
    return m_shared_data_manager;
}

void RenderSystem::beginFrame(fmath::vector4df const& backgroundColor)
{
    ogl::clearBackgroundColor(backgroundColor);
    ogl::clearDepthBuffer();
}

void RenderSystem::endFrame()
{}

}  // namespace haf::sys
