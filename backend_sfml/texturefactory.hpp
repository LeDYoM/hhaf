#pragma once

#ifndef LIB_BACKEND_SFML_TEXTUREFACTORY_HPP
#define LIB_BACKEND_SFML_TEXTUREFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <backend_dev/include/iresourcefactories.hpp>
#include "texture.hpp"

namespace lib::backend::sfmlb
{
	class Texture;
	class TextureFactory : public ITextureFactory
	{
	public:
		ITexture *loadFromFile(const str &file) override;
		ITexture *loadFromRawMemory(RawMemory *raw_memory) override;
		~TextureFactory() override;
	private:
		vector<sptr<Texture>> m_textureCache;
	};
}

#endif
