#ifndef LIB_BACKEND_SFML_TTFONTFACTORY_HPP
#define LIB_BACKEND_SFML_TTFONTFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/backend/ittfontfactory.hpp>
#include "ttfont.hpp"

#include <vector>

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			class TTFontFactory : public ITTFontFactory
			{
			public:
				virtual ITTFont* loadFromFile(const str &file) override;
				virtual ~TTFontFactory();
			private:
				std::vector<TTFont*> m_fontCache;
			};
		}
	}
}

#endif
