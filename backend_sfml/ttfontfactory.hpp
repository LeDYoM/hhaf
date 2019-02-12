#pragma once

#ifndef LIB_BACKEND_SFML_TTFONTFACTORY_HPP
#define LIB_BACKEND_SFML_TTFONTFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <backend_dev/include/iresourcefactories.hpp>
#include "ttfont.hpp"

namespace lib::backend::sfmlb
{
	class TTFontFactory : public ITTFontFactory
	{
	public:
		virtual ITTFont* loadFromFile(const str &file) override;
		virtual ~TTFontFactory();
	private:
		vector<uptr<TTFont>> m_fontCache;
	};
}

#endif
