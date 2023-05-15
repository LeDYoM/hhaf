#include "resource_manager.hpp"
#include "default_resources.hpp"
#include <hlog/include/hlog.hpp>
#include <haf/include/render/vertex_formats.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/resources/image.hpp>

using namespace haf::res;
using namespace haf::core;
using namespace haf::render;

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
    /*
        rManager.createResource("dummy_test_vertex_shader",
                                res::ResourceType::VertexShaderCode,
                                core::str_view{R"(
            #version 450 core

            void main(void)
            {
                const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),
                                               vec4(-0.25, -0.25, 0.5, 1.0),
                                               vec4( 0.25,  0.25, 0.5, 1.0));

                gl_Position = vertices[gl_VertexID];
            }
        )"});

        rManager.createResource("dummy_test_fragment_shader",
                                res::ResourceType::FragmentShaderCode,
                                core::str_view{R"(
            #version 450 core

            out vec4 color;

            void main(void)
            {
                color = vec4(1.0, 0.8, 0.2, 1.0);
            }
        )"});

        rManager.createResourceFromResources(
            "dummy_test_shader", res::ResourceType::Shader,
            {"dummy_test_vertex_shader", "dummy_test_fragment_shader"});

        rManager.aquireResource("dummy_test_shader", m_defaultShaderNoInput);
        LogAsserter::log_assert(m_defaultShaderNoInput != nullptr);

        return m_defaultShaderNoInput != nullptr;
        */
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

bool DefaultResources::loadDefaultBuffers(sys::ResourceManager& rManager)
{
    static vector3df vertex_data_raw[] = {vector3df{0.25F, -0.25F, -1.0F},
                                          vector3df{-0.25F, -0.25F, -1.0F},
                                          vector3df{0.25F, 0.25F, -1.0F}};

    static Position3fNormal3fTextureCoordinates2f vertex_data_raw_mesh[] = {
        Position3fNormal3fTextureCoordinates2f{
            vector3df{0.25F, -0.25F, -1.0F}, Vector3dOnesF32, Vector2dOnesF32},
        Position3fNormal3fTextureCoordinates2f{
            vector3df{-0.25F, -0.25F, -1.0F}, Vector3dOnesF32, Vector2dOnesF32},
        Position3fNormal3fTextureCoordinates2f{
            vector3df{0.25F, 0.25F, -1.0F}, Vector3dOnesF32, Vector2dOnesF32}};

    static vector4df vertex_color_data_raw[] = {
        vector4df{0.0F, 0.0F, 1.0F, 1.0F}, vector4df{1.0F, 0.0F, 0.0F, 1.0F},
        vector4df{0.0F, 1.0F, 0.0F, 1.0F}};

    auto vertex_buffer{core::msptr<res::VertexBufferObject>(
        array{str{"haf_position"}, str{"haf_normal"}, str{"haf_textureuv"}},
        core::span{vertex_data_raw_mesh})};

    auto color_buffer{core::msptr<res::VertexBufferObject>(
        core::array<core::str, 1U>{"haf_color"},
        core::span{vertex_color_data_raw})};

    rManager.addResource("default_position_buffer", vertex_buffer);
    rManager.addResource("default_color_buffer", color_buffer);

    rManager.aquireResource("default_position_buffer", m_defaultPositions);
    LogAsserter::log_assert(m_defaultPositions != nullptr);
    rManager.aquireResource("default_color_buffer", m_defaultColors);
    LogAsserter::log_assert(m_defaultColors != nullptr);

    ///////////////////////////////////////////////////////////////////////////////

    static Position3fNormal3fTextureCoordinates2f quad_data_raw_mesh[] = {
        Position3fNormal3fTextureCoordinates2f{
            vector3df{0.25F, -0.25F, 0.0F}, Vector3dOnesF32, Vector2dOnesF32},
        Position3fNormal3fTextureCoordinates2f{
            vector3df{-0.25F, -0.25F, 0.0F}, Vector3dOnesF32, Vector2dOnesF32},
        Position3fNormal3fTextureCoordinates2f{
            vector3df{0.25F, 0.25F, 0.0F}, Vector3dOnesF32, Vector2dOnesF32},

        Position3fNormal3fTextureCoordinates2f{
            vector3df{0.25F, 0.25F, 1.0F}, Vector3dOnesF32, Vector2dOnesF32},
        Position3fNormal3fTextureCoordinates2f{
            vector3df{-0.25F, 0.25F, 5.0F}, Vector3dOnesF32, Vector2dOnesF32},
        Position3fNormal3fTextureCoordinates2f{vector3df{-0.25F, -0.25F, 10.0F},
                                               Vector3dOnesF32,
                                               Vector2dOnesF32}};

    static vector4df quad_vertex_color_data_raw[] = {
        vector4df{0.0F, 0.0F, 1.0F, 1.0F}, vector4df{1.0F, 0.0F, 0.0F, 1.0F},
        vector4df{0.0F, 1.0F, 0.0F, 1.0F}, vector4df{0.0F, 0.0F, 1.0F, 1.0F},
        vector4df{1.0F, 0.0F, 0.0F, 1.0F}, vector4df{0.0F, 1.0F, 0.0F, 1.0F},
    };

    auto vertex_buffer_quad{core::msptr<res::VertexBufferObject>(
        array{str{"haf_position"}, str{"haf_normal"}, str{"haf_textureuv"}},
        core::span{quad_data_raw_mesh})};

    auto color_buffer_quad{core::msptr<res::VertexBufferObject>(
        str{"haf_color"}, core::span{quad_vertex_color_data_raw})};

    rManager.addResource("quad_position_buffer", vertex_buffer_quad);
    rManager.addResource("quad_color_buffer", color_buffer_quad);

    rManager.aquireResource("quad_position_buffer", m_quadPositions);
    LogAsserter::log_assert(m_quadPositions != nullptr);
    rManager.aquireResource("quad_color_buffer", m_quadColors);
    LogAsserter::log_assert(m_quadColors != nullptr);

    return true;
}

bool DefaultResources::loadDefaultMesh(sys::ResourceManager& rManager)
{
    bool ok{true};
    core::vector<str> ids = {"default_position_buffer", "default_color_buffer"};
    ok &= rManager.createResourceFromResources("default_mesh",
                                               ResourceType::Mesh, ids);

    ids = {"quad_position_buffer", "quad_color_buffer"};
    ok &= rManager.createResourceFromResources("quad_mesh", ResourceType::Mesh,
                                               ids);
    return ok;
}

bool DefaultResources::loadDefaultVertexArrayObject(
    sys::ResourceManager& rManager)
{
    bool ok{true};

    core::vector<str> ids = {"default_shader_0", "default_mesh"};
    ok &= rManager.createResourceFromResources(
        "default_vao", ResourceType::VertexArrayObject, ids);

    ids = {"default_shader_0", "quad_mesh"};
    ok &= rManager.createResourceFromResources(
        "quad_vao", ResourceType::VertexArrayObject, ids);
    return ok;
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
    static Position3fNormal3fTextureCoordinates2f cube_data_raw_mesh[] = {
        {{-0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},
        {{-0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 0.0F}},
        {{0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},
        {{-0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},

        {{0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 0.0F}},
        {{0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},
        {{0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},
        {{0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},

        {{0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{-0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 0.0F}},
        {{0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},
        {{-0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 0.0F}},
        {{-0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},
        {{0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},

        {{-0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{-0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 0.0F}},
        {{-0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},
        {{-0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 0.0F}},
        {{-0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},
        {{-0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},

        {{-0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},
        {{0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},
        {{0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{-0.25F, -0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 0.0F}},
        {{-0.25F, 0.25F, -0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},

        {{-0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 0.0F}},
        {{0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 0.0F}},
        {{0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},
        {{0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {1.0F, 1.0F}},
        {{-0.25F, 0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 1.0F}},
        {{-0.25F, -0.25F, 0.25F}, Vector3dOnesF32, {0.0F, 0.0F}}};

    using namespace scene::colors;

    static vector4df cube_vertex_color_data_raw[] = {
        Cyan, Cyan, Cyan, Cyan, Cyan, Cyan, Blue, Blue, Blue, Blue, Blue, Blue,
        Green, Green, Green, Green, Green, Green, Yellow, Yellow, Yellow,
        Yellow, Yellow, Yellow, Magenta, Magenta, Magenta, Magenta, Magenta,
        Magenta,
        //        Red,     Red,      Red,     Red,     Red,     Red,
        White, White, White, White, White, White, White, White};

    auto vertex_buffer_cube{core::msptr<res::VertexBufferObject>(
        array{str{"haf_position"}, str{"haf_normal"}, str{"haf_textureuv"}},
        core::span{cube_data_raw_mesh})};

    auto color_buffer_cube{core::msptr<res::VertexBufferObject>(
        core::array<core::str, 1U>{"haf_color"},
        core::span{cube_vertex_color_data_raw})};

    bool ok{true};
    ok &= rManager.addResource("default_cube_vertex_data", vertex_buffer_cube);
    ok &= rManager.addResource("default_cube_color_data", color_buffer_cube);

    core::vector<str> ids = {"default_cube_vertex_data",
                             "default_cube_color_data"};
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
