#ifndef LIB_MENU_THEME_INCLUDE_HPP__
#define LIB_MENU_THEME_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/draw/color.hpp>
#include <lib/draw/font.hpp>

namespace lib
{
	namespace gui
	{
		struct CursorDescriptor
		{
			u32 m_nVertex;
			vector2df m_size;
			draw::Color m_color;
		};

		struct Theme
		{
			sptr<draw::TTFont> font;
			draw::Color textColor;
			draw::Color selectedTextColor;
			u32 chSize;
			f32 incY;
			CursorDescriptor cursorDescriptor;
		};
	}
}

#endif
