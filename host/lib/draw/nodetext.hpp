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

			virtual ~NodeText();
			NodeText(const std::string &name);
			NodeText(const std::string &name, const std::string& string, sptr<Font> font, unsigned int characterSize = 30);
			void setString(const std::string &string);
			void setFont(sptr<Font> font);
			void setCharacterSize(const u32 size);
			const std::string & getString() const { return m_string; }
			sptr<Font> getFont() const noexcept { return m_font; }
			u32 getCharacterSize() const noexcept { return m_characterSize; }

			void setPositionWithAlignment(const vector2df &pos, Alignment alignment);
			void setPositionWithAlignmentX(const float x, Alignment alignment = Alignment::Left);
			void setPositionWithAlignmentY(const float y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);

			void setIsBold(const bool v) noexcept { m_isBold = v; }
			void setIsItalic(const bool v) noexcept { m_isItalic = v; }
			void setIsUnderlined(const bool v) noexcept { m_isUnderlined = v; }
			void setIsStrikeThrough(const bool v) noexcept { m_isStrikeThrough = v; }
		private:
			void updateGeometry();

			std::string m_string;
			sptr<Font> m_font;
			u32 m_characterSize;
			bool m_isBold{ false };
			bool m_isItalic{ false };
			bool m_isUnderlined{ false };
			bool m_isStrikeThrough{ false };
		};
	}
}

#endif
