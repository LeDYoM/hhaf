#ifndef LIB_MENU_THEME_INCLUDE_HPP__
#define LIB_MENU_THEME_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/color.hpp>
#include <lib/scene/ttfont.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			struct CursorDescriptor
			{
				u32 m_nVertex;
				vector2df m_size;
				scene::Color m_color;
			};

			struct Theme
			{
				sptr<scene::TTFont> font;
				scene::Color textColor;
				scene::Color selectedTextColor;
				u32 chSize;
				f32 incY;
				CursorDescriptor cursorDescriptor;
			};
		}
	}
}

#endif
