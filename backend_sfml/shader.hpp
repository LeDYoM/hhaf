#pragma once

#ifndef LIB_BACKEND_SFML_SHADER_INCLUDE_HPP
#define LIB_BACKEND_SFML_SHADER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <backend_dev/include/ishader.hpp>

#include <SFML/Graphics/Shader.hpp>

namespace lib::backend::sfmlb
{
    class Shader : public IShader
    {
    public:
        Shader(sf::Shader* shader, const bool owned);
        ~Shader() override;

        void setUniform(const str &name, vector2df v) override;
        void setUniform(const str &name, ITexture *texture) override;

        const sf::Shader &backEndShader() const { return *m_shaderPrivate; }
    private:
        sf::Shader* const m_shaderPrivate;
        bool owned_;
    };
}

#endif
