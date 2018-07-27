#include "shaderfactory.hpp"
#include "shader.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "texture.hpp"

namespace lib::backend::sfmlb
{
	IShader* ShaderFactory::loadFromFile(const str & file)
	{
        uptr<sf::Shader> shader(muptr<sf::Shader>());
        shader->loadFromFile(file.c_str(), sf::Shader::Vertex);
        uptr<Shader> t{ muptr<Shader>(std::move(shader)) };
        m_shaderCache.push_back(std::move(t));
        return (*(m_shaderCache.end() - 1)).get();
    }

    ShaderFactory::~ShaderFactory()
	{
        m_shaderCache.clear();
        m_shaderCache.shrink_to_fit();
    }
}
