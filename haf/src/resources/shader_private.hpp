HAF_PRAGMA_ONCE
#ifndef HAF_RESOURCES_SHADER_SHADER_PRIVATE_INCLUDE_HPP
#define HAF_RESOURCES_SHADER_SHADER_PRIVATE_INCLUDE_HPP

#include <haf/include/resources/shader.hpp>
#include <hogl/include/types.hpp>
#include <htypes/include/menum.hpp>

#include <hogl/include/shader_functions.hpp>
#include <hogl/include/low_level_constants.hpp>
#include "default_shader_data.hpp"

namespace haf::res
{
static_assert(std::is_same_v<ShaderId, ogl::Handle>,
              "ShaderId should be equal to ogl::Handle");

struct Shader::ShaderPrivate
{
    ogl::Handle m_program{ogl::invalidHandle()};
};

using SHType =
    core::MEnum<ShaderType, ShaderType::Vertex, ShaderType::kNumShaderTypes>;

template <typename T>
using SHArray = core::array<T, SHType::size>;

constexpr void loadShaderCodesInHandles(
    SHArray<core::sptr<IShaderCode>>& shader_codes,
    SHArray<ogl::Handle>& shader_handles)
{
    constexpr SHArray<ogl::Handle (*)()> const create_shader_functions{
        ogl::createVertexShader,   ogl::createFragmentShader,
        ogl::createVertexShader,   ogl::createVertexShader,
        ogl::createFragmentShader, ogl::createVertexShader};

    for (SHType::numeric_type index{0}; index < SHType::size; ++index)
    {
        if (shader_codes[index] != nullptr)
        {
            auto const handle{create_shader_functions[index]()};
            shader_handles[SHType{shader_codes[index]->shaderType()}
                               .getNumeric()] = handle;
            (void)(ogl::compileShader(handle, shader_codes[index]->data()));
        }
    }
}

constexpr void attachAllShaders(ogl::Handle const program_handle,
                                SHArray<ogl::Handle> const& shader_handles)
{
    for (const auto& sh_handle : shader_handles)
    {
        if (ogl::isValid(sh_handle))
        {
            ogl::attachShader(program_handle, sh_handle);
        }
    }
}

constexpr void deleteAllShaders(SHArray<ogl::Handle> const& shader_handles)
{
    for (const auto& sh_handle : shader_handles)
    {
        if (ogl::isValid(sh_handle))
        {
            ogl::deleteShader(sh_handle);
        }
    }
}

}  // namespace haf::res

#endif
