#pragma once

#ifndef LIB_BACKEND_SFML_TTFONTFACTORY_HPP
#define LIB_BACKEND_SFML_TTFONTFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/include/backend/ittfontfactory.hpp>
#include "ttfont.hpp"

namespace lib::backend::sfmlb
{
	class TTFontFactory : public ITTFontFactory
	{
	public:
		virtual ITTFont* loadFromFile(const str &file) override;
		virtual ~TTFontFactory();
	private:
		vector<TTFont*> m_fontCache;
	};
}

#endif
