#pragma once

#ifndef LIB_BACKEND_SFML_SHADER_INCLUDE_HPP
#define LIB_BACKEND_SFML_SHADER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/backend/ishader.hpp>

#include <SFML/Graphics/Shader.hpp>

namespace lib::backend::sfmlb
{
	class Shader : public IShader
	{
	public:
        Shader(uptr<sf::Shader> shader);
	private:
        uptr<sf::Shader> m_shaderPrivate;
	};
}

#endif
