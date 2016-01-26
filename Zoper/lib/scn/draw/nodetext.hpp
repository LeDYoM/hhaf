#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include "scenenode.hpp"
#include <string>
#include <vector>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class NodeText : public SceneNode
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

				NodeText();
				virtual ~NodeText();

				NodeText(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30);
				void setString(const sf::String& string);
				void setFont(const sf::Font& font);
				void setCharacterSize(unsigned int size);
				void setStyle(sf::Uint32 style);
				void setColor(const sf::Color& color);
				const sf::String& getString() const;
				const sf::Font* getFont() const;
				unsigned int getCharacterSize() const;
				u32 getStyle() const;
				const color& getColor() const;
				vector2df findCharacterPos(std::size_t index) const;
				virtual floatRect getLocalBounds() const override;
				virtual floatRect getGlobalBounds() const override;
			protected:
				virtual void ensureGeometryUpdate() const override;

			private:
				virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

				sf::String m_string;
				const sf::Font* m_font;
				unsigned int m_characterSize;
				u32 m_style;
				color m_color;
			};
		}
	}
}

#endif
