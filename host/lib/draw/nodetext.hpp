#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include <lib/draw/font.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <vector>

#include "renderizable.hpp"

namespace lib
{
	namespace draw
	{
		class NodeText : public lib::draw::Renderizable
		{
		public:
			enum class Alignment : u8
			{
				Left = 0,
				Center = 1,
				Right = 2
			};

			enum Style
			{
				Regular = 0,      ///< Regular characters, no style
				Bold = 1 << 0, ///< Bold characters
				Italic = 1 << 1, ///< Italic characters
				Underlined = 1 << 2, ///< Underlined characters
				StrikeThrough = 1 << 3  ///< Strike through characters
			};

			virtual ~NodeText();
			NodeText(const std::string &name);
			NodeText(const std::string &name, const sf::String& string, const draw::Font& font, unsigned int characterSize = 30);
			void setString(const std::string &string);
			void setFont(const draw::Font& font);
			void setCharacterSize(u32 size);
			void setStyle(sf::Uint32 style);
			void setColor(const sf::Color& color);
			const std::string & getString() const;
			const draw::Font* getFont() const;
			u32 getCharacterSize() const;
			sf::Uint32 getStyle() const;
			const sf::Color& getColor() const;
			vector2df findCharacterPos(const std::size_t index) const;

			void setPositionWithAlignment(const vector2df &pos, Alignment alignment);
			void setPositionWithAlignmentX(const float x, Alignment alignment = Alignment::Left);
			void setPositionWithAlignmentY(const float y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);

		private:
			virtual void draw(sf::RenderStates &states) override;
			void ensureGeometryUpdate();

			std::string m_string;
			const draw::Font* m_font;
			u32 m_characterSize;
			sf::Uint32 m_style;
			sf::Color m_color;
		};
	}
}

#endif
