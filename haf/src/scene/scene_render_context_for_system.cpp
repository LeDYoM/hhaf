#include "scene_render_context_for_system.hpp"
#include <hlog/include/hlog.hpp>
#include "system/get_system.hpp"
#include "time/time_system.hpp"

namespace haf::scene
{
SceneRenderContextForSystem::SceneRenderContextForSystem(
    sys::ISystemProvider& systemProvider) :
    m_isystem_provider{systemProvider}
{}

void SceneRenderContextForSystem::beginFrame()
{
    auto& timeSystem{sys::getSystem<sys::TimeSystem>(&m_isystem_provider)};
    BaseClass::setNowFrame(timeSystem.nowFrame());
    BaseClass::beginFrame();
}

void SceneRenderContextForSystem::endFrame()
{
    BaseClass::endFrame();
}

}  // namespace haf::scene
