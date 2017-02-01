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
			NodeText(const std::string &name, const std::string& string, sptr<Font> font, u32 characterSize, const Color &color);
			void setFont(sptr<Font> font);
			void setCharacterSize(const u32 size);
			u32 getCharacterSize() const noexcept { return m_characterSize; }
			sptr<Font> getFont() const noexcept { return m_font; }

			void setPositionWithAlignment(const vector2df &pos, Alignment alignment);
			void setPositionWithAlignmentX(const float x, Alignment alignment = Alignment::Left);
			void setPositionWithAlignmentY(const float y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);

			inline void setIsBold(const bool v) noexcept { m_isBold = v; }
			inline void setIsItalic(const bool v) noexcept { m_isItalic = v; }
			inline void setIsUnderlined(const bool v) noexcept { m_isUnderlined = v; }
			inline void setIsStrikeThrough(const bool v) noexcept { m_isStrikeThrough = v; }

			ReadOnlyProperty<Rectf32> bounds;
			Property<std::string> text;
		private:
			void updateGeometry();

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
