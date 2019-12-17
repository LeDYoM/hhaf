#pragma once

#ifndef LIB_SCENE_SHADER_INCLUDE_HPP
#define LIB_SCENE_SHADER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/resources/ishader.hpp>

namespace lib
{
namespace backend
{
class IShader;
}

namespace scene
{
class Shader final : public IShader
{
public:
    Shader(backend::IShader *shader);
    ~Shader() override;

    const backend::IShader* backEndShader() const noexcept { return m_ShaderPrivate; }
private:
    backend::IShader *m_ShaderPrivate;
};
} // namespace scene
} // namespace lib

#endif
