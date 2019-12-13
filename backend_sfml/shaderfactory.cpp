#include "shaderfactory.hpp"
#include "shader.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "texture.hpp"

namespace lib::backend::sfmlb
{
    IShader* ShaderFactory::loadFromFile(const str & file)
    {
        if (::sf::Shader::isAvailable())
        {
            uptr<sf::Shader> shader(muptr<sf::Shader>());
            bool result = shader->loadFromFile(file.c_str(), sf::Shader::Vertex);
            if (result)
            {
                uptr<Shader> t{ muptr<Shader>(shader.release(), true) };
                m_shaderCache.push_back(std::move(t));
                return (*(m_shaderCache.end() - 1)).get();
            }
        }
        return nullptr;
    }

    ShaderFactory::~ShaderFactory()
    {
        m_shaderCache.clear();
        m_shaderCache.shrink_to_fit();
    }
}
