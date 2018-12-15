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

			virtual ITTGlyph getGlyph(const u32 codePoint, const u32 characterSize) const = 0;
			virtual f32 getLineSpacing(const u32 characterSize) const = 0;
			virtual f32 getKerning(const u32 first, const u32 second, const u32 characterSize) const = 0;
			virtual ITexture* getTexture(const u32 characterSize) = 0;
		};
	}
}
#endif
