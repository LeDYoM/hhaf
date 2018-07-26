#pragma once

#ifndef LIB_BACKEND_SFML_SHADER_INCLUDE_HPP__
#define LIB_BACKEND_SFML_SHADER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/include/backend/ishader.hpp>

#include <SFML/Graphics/Shader.hpp>

#include <map>

namespace lib::backend::sfmlb
{
	class Shader : public IShader
	{
	public:
        Shader(const sf::Shader &s);
		virtual ~Shader();
	private:
        sf::Shader m_shader;
	};
}

#endif
