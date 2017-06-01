#ifndef LIB_BACKEND_SFML_TTFONTFACTORY_HPP
#define LIB_BACKEND_SFML_TTFONTFACTORY_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

#include <lib/backend/ittfontfactory.hpp>
#include "ttfont.hpp"

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			class TTFontFactory : public ITTFontFactory
			{
			public:
				virtual sptr<ITTFont> loadFromFile(const str &file) override;
			};
		}
	}
}

#endif
