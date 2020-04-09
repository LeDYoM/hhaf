#pragma once

#ifndef HAF_SCENE_SHADER_INCLUDE_HPP
#define HAF_SCENE_SHADER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/resources/include/ishader.hpp>

namespace haf::backend
{
class IShader;
}

namespace haf::scene
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
} // namespace haf::scene

#endif
