#include "nodetext.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>

#include <lib/core/window.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			NodeText::NodeText(const std::string &name)
				: Renderizable{ name }, m_string(), m_font(nullptr), m_characterSize(30), m_style(Regular),
				m_color(255, 255, 255), m_vertices(sf::Triangles), m_bounds(), m_geometryNeedUpdate(false) {}

			NodeText::NodeText(const std::string &name, const sf::String& string, const sf::Font& font, unsigned int characterSize) :
				Renderizable{ name }, m_string(string), m_font(&font), m_characterSize(characterSize), m_style(Regular),
				m_color(255, 255, 255), m_vertices(sf::Triangles), m_bounds(), m_geometryNeedUpdate(true) {}

			NodeText::~NodeText() {	}

			void NodeText::setString(const std::string & string)
			{
				if (m_string != string)
				{
					m_string = string;
					m_geometryNeedUpdate = true;
				}
			}

			void NodeText::setFont(const sf::Font& font)
			{
				if (m_font != &font)
				{
					m_font = &font;
					m_geometryNeedUpdate = true;
				}
			}

			void NodeText::setCharacterSize(unsigned int size)
			{
				if (m_characterSize != size)
				{
					m_characterSize = size;
					m_geometryNeedUpdate = true;
				}
			}

			void NodeText::setStyle(sf::Uint32 style)
			{
				if (m_style != style)
				{
					m_style = style;
					m_geometryNeedUpdate = true;
				}
			}

			void NodeText::setColor(const sf::Color& color)
			{
				if (color != m_color)
				{
					m_color = color;

					// Change vertex colors directly, no need to update whole geometry
					// (if geometry is updated anyway, we can skip this step)
					if (!m_geometryNeedUpdate)
					{
						for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
							m_vertices[i].color = m_color;
					}
				}
			}

			const std::string & NodeText::getString() const
			{
				return m_string;
			}

			const sf::Font* NodeText::getFont() const
			{
				return m_font;
			}

			unsigned int NodeText::getCharacterSize() const
			{
				return m_characterSize;
			}

			sf::Uint32 NodeText::getStyle() const
			{
				return m_style;
			}

			const sf::Color& NodeText::getColor() const
			{
				return m_color;
			}

			sf::Vector2f NodeText::findCharacterPos(std::size_t index) const
			{
				// Make sure that we have a valid font
				if (!m_font)
					return sf::Vector2f();

				// Adjust the index if it's out of range
				if (index > m_string.length())
					index = m_string.length();

				// Precompute the variables needed by the algorithm
				bool  bold = (m_style & Bold) != 0;
				float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
				float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));

				// Compute the position
				sf::Vector2f position;
				sf::Uint32 prevChar = 0;
				for (std::size_t i = 0; i < index; ++i)
				{
					sf::Uint32 curChar = m_string[i];

					// Apply the kerning offset
					position.x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
					prevChar = curChar;

					// Handle special characters
					switch (curChar)
					{
					case ' ':  position.x += hspace;                 continue;
					case '\t': position.x += hspace * 4;             continue;
					case '\n': position.y += vspace; position.x = 0; continue;
					}

					// For regular characters, add the advance offset of the glyph
					position.x += static_cast<float>(m_font->getGlyph(curChar, m_characterSize, bold).advance);
				}

				// Transform the position to global coordinates
				position = getTransform().transformPoint(position);

				return position;
			}

			sf::FloatRect NodeText::getLocalBounds() const
			{
				ensureGeometryUpdate();

				return m_bounds;
			}

			sf::FloatRect NodeText::getGlobalBounds() const
			{
				return getTransform().transformRect(getLocalBounds());
			}

			lib::u32 NodeText::draw(lib::core::Window *window, sf::RenderStates &states)
			{
				if (m_font)
				{
					ensureGeometryUpdate();

					auto oldTransform = states.transform;
					states.transform *= getTransform();
					states.texture = &m_font->getTexture(m_characterSize);
					window->draw(m_vertices, states);
					states.transform = oldTransform;
					return 1;
				}
				return 0;
			}

			void NodeText::ensureGeometryUpdate() const
			{
				// Do nothing, if geometry has not changed
//				if (!m_geometryNeedUpdate)
//					return;

				// Mark geometry as updated
				m_geometryNeedUpdate = false;

				// Clear the previous geometry
				m_vertices.clear();
				m_bounds = sf::FloatRect();

				// No font: nothing to draw
				if (!m_font)
					return;

				// No text: nothing to draw
				if (m_string.empty())
					return;

				// Compute values related to the text style
				bool  bold = (m_style & Bold) != 0;
				bool  underlined = (m_style & Underlined) != 0;
				bool  strikeThrough = (m_style & StrikeThrough) != 0;
				float italic = (m_style & Italic) ? 0.208f : 0.f; // 12 degrees
				float underlineOffset = m_font->getUnderlinePosition(m_characterSize);
				float underlineThickness = m_font->getUnderlineThickness(m_characterSize);

				// Compute the location of the strike through dynamically
				// We use the center point of the lowercase 'x' glyph as the reference
				// We reuse the underline thickness as the thickness of the strike through as well
				sf::FloatRect xBounds = m_font->getGlyph(L'x', m_characterSize, bold).bounds;
				float strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

				// Precompute the variables needed by the algorithm
				float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
				float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));
				float x = 0.f;
				float y = static_cast<float>(m_characterSize);

				// Create one quad for each character
				float minX = static_cast<float>(m_characterSize);
				float minY = static_cast<float>(m_characterSize);
				float maxX = 0.f;
				float maxY = 0.f;
				sf::Uint32 prevChar = 0;
				for (std::size_t i = 0; i < m_string.length(); ++i)
				{
					sf::Uint32 curChar = m_string[i];

					// Apply the kerning offset
					x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
					prevChar = curChar;

					// If we're using the underlined style and there's a new line, draw a line
					if (underlined && (curChar == L'\n'))
					{
						float top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
						float bottom = top + std::floor(underlineThickness + 0.5f);

						m_vertices.append(sf::Vertex(sf::Vector2f(0, top), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(x, bottom), m_color, sf::Vector2f(1, 1)));
					}

					// If we're using the strike through style and there's a new line, draw a line across all characters
					if (strikeThrough && (curChar == L'\n'))
					{
						float top = std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f);
						float bottom = top + std::floor(underlineThickness + 0.5f);

						m_vertices.append(sf::Vertex(sf::Vector2f(0, top), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
						m_vertices.append(sf::Vertex(sf::Vector2f(x, bottom), m_color, sf::Vector2f(1, 1)));
					}

					// Handle special characters
					if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
					{
						// Update the current bounds (min coordinates)
						minX = std::min(minX, x);
						minY = std::min(minY, y);

						switch (curChar)
						{
						case ' ':  x += hspace;        break;
						case '\t': x += hspace * 4;    break;
						case '\n': y += vspace; x = 0; break;
						}

						// Update the current bounds (max coordinates)
						maxX = std::max(maxX, x);
						maxY = std::max(maxY, y);

						// Next glyph, no need to create a quad for whitespace
						continue;
					}

					// Extract the current glyph's description
					const sf::Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, bold);

					float left = glyph.bounds.left;
					float top = glyph.bounds.top;
					float right = glyph.bounds.left + glyph.bounds.width;
					float bottom = glyph.bounds.top + glyph.bounds.height;

					float u1 = static_cast<float>(glyph.textureRect.left);
					float v1 = static_cast<float>(glyph.textureRect.top);
					float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width);
					float v2 = static_cast<float>(glyph.textureRect.top + glyph.textureRect.height);

					// Add a quad for the current character
					m_vertices.append(sf::Vertex(sf::Vector2f(x + left - italic * top, y + top), m_color, sf::Vector2f(u1, v1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x + right - italic * top, y + top), m_color, sf::Vector2f(u2, v1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x + left - italic * bottom, y + bottom), m_color, sf::Vector2f(u1, v2)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x + left - italic * bottom, y + bottom), m_color, sf::Vector2f(u1, v2)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x + right - italic * top, y + top), m_color, sf::Vector2f(u2, v1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x + right - italic * bottom, y + bottom), m_color, sf::Vector2f(u2, v2)));

					// Update the current bounds
					minX = std::min(minX, x + left - italic * bottom);
					maxX = std::max(maxX, x + right - italic * top);
					minY = std::min(minY, y + top);
					maxY = std::max(maxY, y + bottom);

					// Advance to the next character
					x += glyph.advance;
				}

				// If we're using the underlined style, add the last line
				if (underlined)
				{
					float top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
					float bottom = top + std::floor(underlineThickness + 0.5f);

					m_vertices.append(sf::Vertex(sf::Vector2f(0, top), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x, bottom), m_color, sf::Vector2f(1, 1)));
				}

				// If we're using the strike through style, add the last line across all characters
				if (strikeThrough)
				{
					float top = std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f);
					float bottom = top + std::floor(underlineThickness + 0.5f);

					m_vertices.append(sf::Vertex(sf::Vector2f(0, top), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(0, bottom), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
					m_vertices.append(sf::Vertex(sf::Vector2f(x, bottom), m_color, sf::Vector2f(1, 1)));
				}

				// Update the bounding rectangle
				m_bounds.left = minX;
				m_bounds.top = minY;
				m_bounds.width = maxX - minX;
				m_bounds.height = maxY - minY;
			}
		}
	}
}
