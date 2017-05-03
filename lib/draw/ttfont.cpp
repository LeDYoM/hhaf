#ifndef LIB_DRAW_TTFONT_INCLUDE_HPP__
#define LIB_DRAW_TTFONT_INCLUDE_HPP__

#include <SFML/Graphics/Font.hpp>
#include <lib/draw/hasname.hpp>

namespace lib
{
	namespace draw
	{
		class TTFont final : public sf::Font, public core::HasName
		{
		public:
			TTFont(str name) : core::HasName{ std::move(name) }, sf::Font{} {}

			virtual ~TTFont() {}
		};
	}
}

#endif
