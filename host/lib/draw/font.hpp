#ifndef LIB_DRAW_FONT_INCLUDE_HPP__
#define LIB_DRAW_FONT_INCLUDE_HPP__

#include <SFML/Graphics/Font.hpp>
#include <lib/draw/hasname.hpp>

namespace lib
{
	namespace draw
	{
		class Font : public sf::Font, public core::HasName
		{
		public:
			Font(std::string name) : core::HasName(name), sf::Font{} {}

			virtual ~Font() {}
		};
	}
}

#endif
