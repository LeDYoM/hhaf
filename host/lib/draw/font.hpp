#ifndef LIB_DRAW_FONT_INCLUDE_HPP__
#define LIB_DRAW_FONT_INCLUDE_HPP__

#include <SFML/Graphics/Font.hpp>

namespace lib
{
	namespace draw
	{
		class Font : public sf::Font
		{
		public:
			using sf::Font::Font;

			virtual ~Font() {}
		};
	}
}

#endif
