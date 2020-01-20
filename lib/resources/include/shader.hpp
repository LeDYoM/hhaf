#pragma once

#ifndef LIB_SCENE_SHADER_INCLUDE_HPP
#define LIB_SCENE_SHADER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/resources_interface/include/ishader.hpp>

namespace lib::backend
{
class IShader;
}

namespace lib::scene
{
class Shader final : public IShader
{
public:
    Shader(backend::IShader *shader);
    ~Shader() override;

    const backend::IShader *backEndShader() const noexcept { return m_ShaderPrivate; }

private:
    backend::IShader *m_ShaderPrivate;
};
} // namespace lib::scene

#endif
