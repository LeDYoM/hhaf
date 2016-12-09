#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include "renderizable.hpp"
#include "font.hpp"
#include "texture.hpp"

#include <string>
#include <vector>

namespace lib
{
	namespace draw
	{
		class NodeText : public Renderizable
		{
		public:
			enum class Alignment : u8
			{
				Left = 0,
				Center = 1,
				Right = 2
			};

			enum Style : u8
			{
				Regular = 0,
				Bold = 1 << 0,
				Italic = 1 << 1,
				Underlined = 1 << 2,
				StrikeThrough = 1 << 3
			};

			virtual ~NodeText();
			NodeText(const std::string &name);
			NodeText(const std::string &name, const std::string& string, sptr<Font> font, unsigned int characterSize = 30);
			void setString(const std::string &string);
			void setFont(sptr<Font> font);
			void setCharacterSize(const u32 size);
			void setStyle(const Style style);
			inline Style getStyle() const noexcept { return m_style; }
			const std::string & getString() const { return m_string; }
			sptr<Font> getFont() const noexcept { return m_font; }
			u32 getCharacterSize() const noexcept { return m_characterSize; }

			void setPositionWithAlignment(const vector2df &pos, Alignment alignment);
			void setPositionWithAlignmentX(const float x, Alignment alignment = Alignment::Left);
			void setPositionWithAlignmentY(const float y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);

		private:
			void updateGeometry();

			std::string m_string;
			sptr<Font> m_font;
			u32 m_characterSize;
			Style m_style;
		};
	}
}

#endif
