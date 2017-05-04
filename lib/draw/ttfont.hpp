#ifndef LIB_DRAW_TTFONT_INCLUDE_HPP__
#define LIB_DRAW_TTFONT_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>
#include <lib/draw/texture.hpp>
#include <lib/draw/hasname.hpp>
#include <lib/backend/ittfont.hpp>

namespace sf
{
	class Font;
}

namespace lib
{
	namespace backend
	{
		class IFont;
	}

	namespace draw
	{
		struct TTGlyph final : public backend::ITTGlyph
		{
		};

		class TTFont final : public core::HasName
		{
		public:
			TTFont(str name);
			~TTFont();

			bool loadFromFile(const std::string& filename);
			const TTGlyph getGlyph(u32 codePoint, u32 characterSize, bool bold, f32 outlineThickness) const;
			f32 getLineSpacing(u32 characterSize) const;
			f32 getKerning(u32 first, u32 second, u32 characterSize) const;
			const Texture getTexture(u32 characterSize) const;

		private:
			sptr<backend::ITTFont> m_font;
		};
	}
}

#endif
