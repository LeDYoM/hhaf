#include "scene_render_context_for_system.hpp"
#include <hlog/include/hlog.hpp>
#include "system/get_system.hpp"
#include "time/time_system.hpp"

#include "system/get_system.hpp"
#include "resources/resource_manager.hpp"
#include "render/render_system.hpp"

#include "glad/glad.h"
#include <hogl/include/buffer_functions.hpp>
#include <haf/include/render/render_buffer.hpp>
#include <haf/include/render/shared_data_buffer.hpp>
#include <haf/include/render/vertex_formats.hpp>

using namespace haf::core;
using namespace fmath;

namespace haf::scene
{
SceneRenderContextForSystem::SceneRenderContextForSystem(
    sys::ISystemProvider& systemProvider) :
    m_isystem_provider{systemProvider}
{}

void SceneRenderContextForSystem::init()
{
    BaseClass::init();
}

void SceneRenderContextForSystem::beginFrame()
{
    auto& timeSystem{sys::getSystem<sys::TimeSystem>(&m_isystem_provider)};
    BaseClass::setNowFrame(timeSystem.nowFrame());
    BaseClass::beginFrame();

    auto& renderSystem{sys::getSystem<sys::RenderSystem>(&m_isystem_provider)};
    renderSystem.beginFrame(m_backgroundColor);
}

void SceneRenderContextForSystem::endFrame()
{
    BaseClass::endFrame();
}

void SceneRenderContextForSystem::setCameraMatrix(Matrix4x4 const& matrix)
{
    BaseClass::setCameraMatrix(matrix);

    auto sh_buffer = sys::getSystem<sys::RenderSystem>(&m_isystem_provider)
                         .sharedDataManager()
                         .get("haf_camera_projection");

    if (!sh_buffer)
    {
        sh_buffer = msptr<render::SharedDataBuffer>(
            "HAFCameraData", span<Matrix4x4>{});
        sh_buffer->autoBindToDefault();

        sys::getSystem<sys::RenderSystem>(&m_isystem_provider)
            .sharedDataManager()
            .add("haf_camera_projection", sh_buffer);
    }

    sh_buffer->write<Matrix4x4>(matrix);
}

}  // namespace haf::scene
