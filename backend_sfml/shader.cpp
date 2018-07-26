#include "shader.hpp"
#include "conversions.hpp"

namespace lib::backend::sfmlb
{
    Shader::Shader(const sf::Shader & s) : m_shader{ s } {}

    Shader::~Shader()
    {
	}
}
