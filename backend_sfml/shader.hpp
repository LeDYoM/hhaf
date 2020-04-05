#pragma once

#ifndef LIB_BACKEND_SFML_SHADER_INCLUDE_HPP
#define LIB_BACKEND_SFML_SHADER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <backend_dev/include/ishader.hpp>

#include <SFML/Graphics/Shader.hpp>

namespace haf::backend::sfmlb
{
class Shader : public IShader
{
public:
    Shader(mtps::uptr<sf::Shader> shader);
    ~Shader() override;

    void setUniform(const mtps::str &name, mtps::vector2df v) override;
    void setUniform(const mtps::str &name, ITexture *texture) override;

    const sf::Shader &backEndShader() const { return *m_shaderPrivate; }

private:
    mtps::uptr<sf::Shader> m_shaderPrivate;
};
} // namespace haf::backend::sfmlb

#endif
