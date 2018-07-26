#include "shaderfactory.hpp"
#include "shader.hpp"
#include <SFML/Graphics/Shader.hpp>
#include "texture.hpp"

namespace lib::backend::sfmlb
{
	IShader* ShaderFactory::loadFromFile(const str & file)
	{
		sf::Font font;
		font.loadFromFile(file.c_str());
		auto *ttffont(new TTFont(font));
		m_fontCache.push_back(ttffont);
		return ttffont;
	}

    ShaderFactory::~ShaderFactory()
	{
		for (auto *font : m_fontCache) {
			delete font;
		}
		m_fontCache.clear();
	}
}
