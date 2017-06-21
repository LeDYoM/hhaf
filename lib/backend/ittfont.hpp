#ifndef LIB_BACKEND_ITTFONT_HPP
#define LIB_BACKEND_ITTFONT_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include "itexture.hpp"

namespace lib
{
	namespace backend
	{
		struct ITTGlyph
		{
			Rectf32 bounds;
			Rectf32 textureBounds;
			f32 advance;
		};

		class ITTFont
		{
		public:
			ITTFont() {}
			virtual ~ITTFont() {}

			virtual const ITTGlyph getGlyph(u32 codePoint, u32 characterSize, bool bold, f32 outlineThickness) const = 0;
			virtual f32 getLineSpacing(u32 characterSize) const = 0;
			virtual f32 getKerning(u32 first, u32 second, u32 characterSize) const = 0;
			virtual ITexture* getTexture(u32 characterSize) = 0;
		};
	}
}
#endif
