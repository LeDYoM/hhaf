#ifndef LIB_MENU_THEME_INCLUDE_HPP__
#define LIB_MENU_THEME_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <SFML/Graphics/Color.hpp>
#include <lib/draw/font.hpp>


namespace lib
{
	namespace menu
	{
		struct CursorDescriptor
		{
		public:
			u32 m_nVertex;
			vector2df m_size;
			sf::Color m_color;
		};

		struct Theme
		{
			sptr<draw::Font> font;
			sf::Color textColor;
			sf::Color selectedTextColor;
			u32 chSize;
			f32 incY;
			CursorDescriptor cursorDescriptor;
		};
	}
}

#endif
