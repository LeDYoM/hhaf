#include "scene_render_context_for_system.hpp"
#include <hlog/include/hlog.hpp>
#include "system/get_system.hpp"
#include "time/time_system.hpp"

#include "system/get_system.hpp"
#include "resources/resource_manager.hpp"

#include "glad/glad.h"
#include <hogl/include/buffer_functions.hpp>
#include <haf/include/render/render_buffer.hpp>
#include <haf/include/render/shared_data_buffer.hpp>
#include <haf/include/render/vertex_formats.hpp>

GLuint bufferUniform;
GLuint bindingpoint = 1;

namespace haf::scene
{
render::SharedDataBuffer* sh_buffer{nullptr};

SceneRenderContextForSystem::SceneRenderContextForSystem(
    sys::ISystemProvider& systemProvider) :
    m_isystem_provider{systemProvider}
{}

void SceneRenderContextForSystem::beginFrame()
{
    auto& timeSystem{sys::getSystem<sys::TimeSystem>(&m_isystem_provider)};
    BaseClass::setNowFrame(timeSystem.nowFrame());
    BaseClass::beginFrame();

    if (!sh_buffer)
    {
        using namespace render;
        CameraData data{};
        core::span<CameraData> _data(data);
        sh_buffer =
            new render::SharedDataBuffer{"HAFCameraData", core::move(_data)};
    }
}

void SceneRenderContextForSystem::endFrame()
{
    BaseClass::endFrame();
}

void SceneRenderContextForSystem::setCameraMatrix(math::Matrix4x4 const& matrix)
{
    BaseClass::setCameraMatrix(matrix);
    /*
        [[maybe_unused]] auto const count{
            sys::getSystem<sys::ResourceManager>(&m_isystem_provider)
                .shaderManager()
                .setUniformForAll("haf_camera_projection", m_cameraMatrix())};
    */

    render::CameraData cameraData;
    cameraData.projection = matrix;
//    sh_buffer->setBindingPoint(bindingpoint);
    sh_buffer->autoBindToDefault();
    sh_buffer->write<render::CameraData>(cameraData);
//    glBindBufferBase(GL_UNIFORM_BUFFER, bindingpoint, bufferUniform);
//    math::Matrix4x4* mat = static_cast<math::Matrix4x4*>(
//        glMapNamedBufferRange(bufferUniform, 0, sizeof(math::Matrix4x4),
//                              GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));

//    *mat = m_cameraMatrix();  // math::Matrix4x4::Identity;
//    glUnmapNamedBuffer(bufferUniform);
}

}  // namespace haf::scene
