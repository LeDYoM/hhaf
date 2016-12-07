#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include "renderizable.hpp"

#include <lib/draw/font.hpp>

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
			virtual void setColor(const Color color) override;
			const std::string & getString() const { return m_string; }
			sptr<Font> getFont() const noexcept { return m_font; }
			u32 getCharacterSize() const noexcept { return m_characterSize; }
			Color getColor() const;
			vector2df findCharacterPos(const std::size_t index) const;

			void setPositionWithAlignment(const vector2df &pos, Alignment alignment);
			void setPositionWithAlignmentX(const float x, Alignment alignment = Alignment::Left);
			void setPositionWithAlignmentY(const float y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);

		private:
			virtual void draw() override;
			void updateGeometry();

			std::string m_string;
			sptr<Font> m_font;
			const sf::Texture *m_currentTexture;
			u32 m_characterSize;
			Style m_style;
			Color m_color;
		};
	}
}

#endif
