#include "resource_manager.hpp"
#include "default_resources.hpp"
#include <hlog/include/hlog.hpp>
#include <haf/include/render/vertex_formats.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/resources/image.hpp>

using namespace haf::res;
using namespace haf::core;
using namespace haf::render;
using namespace fmath;

namespace haf::res
{
bool DefaultResources::loadDefaultResources(sys::ResourceManager& rManager)
{
    bool result{true};
    result &= loadDefaultShaderNoInput(rManager);
    result &= loadDefaultShader0(rManager);
    result &= loadDefaultBuffers(rManager);
    result &= loadDefaultMesh(rManager);
    result &= loadDefaultVertexArrayObject(rManager);
    result &= loadDefaultCubeMesh(rManager);
    return result;
}

bool DefaultResources::loadDefaultShaderNoInput(
    sys::ResourceManager& /*rManager*/)
{
    return true;
}

bool DefaultResources::loadDefaultShader0(sys::ResourceManager& rManager)
{
    rManager.createResource("default_vertex_shader_0",
                            res::ResourceType::VertexShaderCode,
                            core::str_view{R"(
        #version 450 core

        in vec3 haf_position;
        in vec4 haf_color;
        in vec2 haf_textureuv;

        uniform mat4 haf_camera_projection;
        uniform mat4 haf_object_position;

        layout(std140,location=1) uniform Foo
        {
            float a;
            float b;
            float c;
            float d;
        };

        layout(std140) uniform HAFCameraData
        {
            mat4 haf_projection;
        };

        out vec4 haf_out_color;
        out vec2 haf_out_textureuv;

        void main(void)
        {
            gl_Position = haf_projection *
                haf_object_position * vec4(haf_position.xyz, 1.0f);

            haf_out_color = haf_color;
            haf_out_textureuv = haf_textureuv;
        }
    )"});

    rManager.createResource("default_fragment_shader_0",
                            res::ResourceType::FragmentShaderCode,
                            core::str_view{R"(
        #version 450 core
        in vec4 haf_out_color;
        in vec2 haf_out_textureuv;
        out vec4 color;

        uniform sampler2D haf_textureuv;

        void main(void)
        {
            color = haf_out_color;
            color = color * texture( haf_textureuv, haf_out_textureuv );
        }
    )"});

    rManager.createResourceFromResources(
        "default_shader_0", res::ResourceType::Shader,
        {"default_vertex_shader_0", "default_fragment_shader_0"});

    rManager.aquireResource("default_shader_0", m_defaultShader0);
    LogAsserter::log_assert(m_defaultShader0 != nullptr);

    return m_defaultShader0 != nullptr;
}

bool DefaultResources::loadDefaultBuffers(sys::ResourceManager&)
{
    return true;
}

bool DefaultResources::loadDefaultMesh(sys::ResourceManager& rManager)
{
    bool ok{true};
    core::vector<str> ids = {"quad_position_buffer", "quad_color_buffer"};
    ok &= rManager.createResourceFromResources("quad_mesh", ResourceType::Mesh,
                                               ids);
    return ok;
}

bool DefaultResources::loadDefaultVertexArrayObject(
    sys::ResourceManager&)
{
    return true;
}

sptr<Shader> DefaultResources::getDefaultShaderNoInput() const
{
    return m_defaultShaderNoInput;
}

sptr<Shader> DefaultResources::getDefaultShader0() const
{
    return m_defaultShader0;
}

sptr<VertexBufferObject> DefaultResources::getDefaultPositionRenderDataBufer()
    const
{
    return m_defaultPositions;
}

sptr<VertexBufferObject> DefaultResources::getDefaultColorRenderDataBufer()
    const
{
    return m_defaultColors;
}

bool DefaultResources::loadDefaultCubeMesh(sys::ResourceManager& rManager)
{
    static vector3df cube_data_raw_mesh_position[] = {
        {-0.25F, -0.25F, 0.25F},  {-0.25F, -0.25F, -0.25F},
        {0.25F, -0.25F, -0.25F},  {0.25F, -0.25F, -0.25F},
        {0.25F, -0.25F, 0.25F},   {-0.25F, -0.25F, 0.25F},

        {0.25F, -0.25F, -0.25F},  {0.25F, 0.25F, -0.25F},
        {0.25F, -0.25F, 0.25F},   {0.25F, 0.25F, -0.25F},
        {0.25F, 0.25F, 0.25F},    {0.25F, -0.25F, 0.25F},

        {0.25F, 0.25F, -0.25F},   {-0.25F, 0.25F, -0.25F},
        {0.25F, 0.25F, 0.25F},    {-0.25F, 0.25F, -0.25F},
        {-0.25F, 0.25F, 0.25F},   {0.25F, 0.25F, 0.25F},

        {-0.25F, 0.25F, -0.25F},  {-0.25F, -0.25F, -0.25F},
        {-0.25F, 0.25F, 0.25F},   {-0.25F, -0.25F, -0.25F},
        {-0.25F, -0.25F, 0.25F},  {-0.25F, 0.25F, 0.25F},

        {-0.25F, 0.25F, -0.25F},  {0.25F, 0.25F, -0.25F},
        {0.25F, -0.25F, -0.25F},  {0.25F, -0.25F, -0.25F},
        {-0.25F, -0.25F, -0.25F}, {-0.25F, 0.25F, -0.25F},

        {-0.25F, -0.25F, 0.25F},  {0.25F, -0.25F, 0.25F},
        {0.25F, 0.25F, 0.25F},    {0.25F, 0.25F, 0.25F},
        {-0.25F, 0.25F, 0.25F},   {-0.25F, -0.25F, 0.25F}};

    static vector3df cube_data_raw_mesh_normal[] = {
        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,
        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,

        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,
        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,

        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,
        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,

        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,
        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,

        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,
        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,

        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32,
        Vector3dOnesF32, Vector3dOnesF32, Vector3dOnesF32};

    static vector2df cube_data_raw_mesh_textureuv[] = {
        {0.0F, 1.0F}, {0.0F, 0.0F}, {1.0F, 0.0F},
        {1.0F, 0.0F}, {1.0F, 1.0F}, {0.0F, 1.0F},

        {0.0F, 0.0F}, {1.0F, 0.0F}, {0.0F, 1.0F},
        {1.0F, 0.0F}, {1.0F, 1.0F}, {0.0F, 1.0F},

        {1.0F, 0.0F}, {0.0F, 0.0F}, {1.0F, 1.0F},
        {0.0F, 0.0F}, {0.0F, 1.0F}, {1.0F, 1.0F},

        {1.0F, 0.0F}, {0.0F, 0.0F}, {1.0F, 1.0F},
        {0.0F, 0.0F}, {0.0F, 1.0F}, {1.0F, 1.0F},

        {0.0F, 1.0F}, {1.0F, 1.0F}, {1.0F, 0.0F},
        {1.0F, 0.0F}, {0.0F, 0.0F}, {0.0F, 1.0F},

        {0.0F, 0.0F}, {1.0F, 0.0F}, {1.0F, 1.0F},
        {1.0F, 1.0F}, {0.0F, 1.0F}, {0.0F, 0.0F}};

    using namespace scene::colors;

    static vector4df cube_vertex_color_data_raw[] = {
        Cyan,    Cyan,    Cyan,    Cyan,    Cyan,    Cyan,    Blue,   Blue,
        Blue,    Blue,    Blue,    Blue,    Green,   Green,   Green,  Green,
        Green,   Green,   Yellow,  Yellow,  Yellow,  Yellow,  Yellow, Yellow,
        Magenta, Magenta, Magenta, Magenta, Magenta, Magenta, White,  White,
        White,   White,   White,   White,   White,   White};

    auto color_buffer_cube{core::msptr<res::VertexBufferObject>(
        "haf_color", core::span{cube_vertex_color_data_raw})};

    auto vertex_buffer_cube_positions{core::msptr<res::VertexBufferObject>(
        "haf_position", core::span{cube_data_raw_mesh_position})};

    auto vertex_buffer_cube_normals{core::msptr<res::VertexBufferObject>(
        "haf_normal", core::span{cube_data_raw_mesh_normal})};

    auto vertex_buffer_cube_textureuvs{core::msptr<res::VertexBufferObject>(
        "haf_textureuv", core::span{cube_data_raw_mesh_textureuv})};

    bool ok{true};
    ok &= rManager.addResource("default_cube_color_data", color_buffer_cube);
    ok &= rManager.addResource("default_cube_positions_data",
                               vertex_buffer_cube_positions);
    ok &= rManager.addResource("default_cube_normals_data",
                               vertex_buffer_cube_normals);
    ok &= rManager.addResource("default_cube_textureuvs_data",
                               vertex_buffer_cube_textureuvs);

    core::vector<str> ids = {
        "default_cube_positions_data", "default_cube_normals_data",
        "default_cube_textureuvs_data", "default_cube_color_data"};
    ok &= rManager.createResourceFromResources("cube_mesh", ResourceType::Mesh,
                                               ids);

    ids = {"default_shader_0", "cube_mesh"};
    ok &= rManager.createResourceFromResources(
        "cube_vao", ResourceType::VertexArrayObject, ids);

    auto image{core::msptr<res::Image>("a")};
    auto texture{core::msptr<res::Texture>(*image)};
    ok &= rManager.addResource("default_texture", texture);

    return ok;
}

}  // namespace haf::res
