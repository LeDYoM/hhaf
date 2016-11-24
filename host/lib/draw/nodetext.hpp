#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
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
			NodeText(const std::string &name, const sf::String& string, const sf::Font& font, unsigned int characterSize = 30);
			void setString(const std::string &string);
			void setFont(const sf::Font& font);
			void setCharacterSize(u32 size);
			void setStyle(sf::Uint32 style);
			void setColor(const sf::Color& color);
			const std::string & getString() const;
			const sf::Font* getFont() const;
			unsigned int getCharacterSize() const;
			sf::Uint32 getStyle() const;
			const sf::Color& getColor() const;
			vector2df findCharacterPos(std::size_t index) const;
			Rectf32 getLocalBounds() const override;
			Rectf32 getGlobalBounds() const override;
		private:
			virtual u32 draw(sf::RenderStates &states) override;
			void ensureGeometryUpdate();

			std::string m_string;
			const sf::Font* m_font;
			u32 m_characterSize;
			sf::Uint32 m_style;
			sf::Color m_color;
			sf::VertexArray m_vertices;
			Rectf32 m_bounds;
		};
	}
}

#endif
