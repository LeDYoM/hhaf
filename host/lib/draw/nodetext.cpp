#include "nodetext.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>

#include <lib/core/host.hpp>
#include <lib/core/window.hpp>

namespace lib
{
	namespace draw
	{
		NodeText::NodeText(const std::string &name)
			:NodeText(name, sf::String{},nullptr,30) {}

		NodeText::NodeText(const std::string &name, const std::string& string, sptr<Font> font, unsigned int characterSize) :
			Renderizable{ name, Triangles }, m_string(string), m_font{ font }, m_characterSize{ characterSize }, m_style{ Regular },
			m_color{ 255, 255, 255 } {}

		NodeText::~NodeText() {	}

		void NodeText::setString(const std::string & string)
		{
			if (m_string != string)
			{
				m_string = string;
				ensureGeometryUpdate();
			}
		}

		void NodeText::setFont(sptr<Font> font)
		{
			if (m_font != font) {
				m_font = font;
				ensureGeometryUpdate();
			}
		}

		void NodeText::setCharacterSize(const u32 size)
		{
			if (m_characterSize != size) {
				m_characterSize = size;
				ensureGeometryUpdate();
			}
		}

		void NodeText::setStyle(const Style style)
		{
			if (m_style != style) {
				m_style = style;
				ensureGeometryUpdate();
			}
		}

		void NodeText::setColor(const Color color)
		{
			if (color != m_color) {
				m_color = color;

				for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
					m_vertices[i].color = m_color;
			}
		}

		const std::string & NodeText::getString() const
		{
			return m_string;
		}

		sptr<Font> NodeText::getFont() const
		{
			return m_font;
		}

		u32 NodeText::getCharacterSize() const
		{
			return m_characterSize;
		}

		NodeText::Style NodeText::getStyle() const
		{
			return m_style;
		}

		Color NodeText::getColor() const
		{
			return m_color;
		}

		vector2df NodeText::findCharacterPos(const std::size_t cindex) const
		{
			// Make sure that we have a valid font
			if (!m_font)
				return vector2df{};

			// Adjust the index if it's out of range
			decltype(cindex) index = (cindex > m_string.length() ? m_string.length() : cindex);

			// Precompute the variables needed by the algorithm
			const bool  bold = (m_style & Bold) != 0;
			f32 hspace = m_font->getGlyph(L' ', m_characterSize, bold).advance;
			f32 vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));

			// Compute the position
			vector2df position;
			std::string::value_type prevChar{ 0 };
			for (std::size_t i = 0; i < index; ++i)
			{
				auto curChar = m_string[i];

				// Apply the kerning offset
				position.x += m_font->getKerning(prevChar, curChar, m_characterSize);
				prevChar = curChar;

				// Handle special characters
				switch (curChar)
				{
				case ' ':  position.x += hspace;                 continue;
				case '\t': position.x += hspace * 4;             continue;
				case '\n': position.y += vspace; position.x = 0; continue;
				}

				// For regular characters, add the advance offset of the glyph
				position.x += m_font->getGlyph(curChar, m_characterSize, bold).advance;
			}

			// Transform the position to global coordinates
			position = getTransform().transformPoint(position);

			return position;
		}

		void NodeText::draw(sf::RenderStates &states)
		{
			if (m_font) {
				ensureGeometryUpdate();

				auto oldTransform = states.transform;
				states.transform *= getTransform();
				states.texture = &m_font->getTexture(m_characterSize);
				host().parentWindow().draw((const sf::Vertex*)&m_vertices[0], m_vertices.getVertexCount(), static_cast<sf::PrimitiveType>(m_vertices.getPrimitiveType()), states);
				states.transform = oldTransform;
			}
		}

		void NodeText::ensureGeometryUpdate()
		{
			// Clear the previous geometry
			m_vertices.clear();
			m_bounds = Rectf32{};

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
			sf::FloatRect glyphRect(m_font->getGlyph(L'x', m_characterSize, bold).bounds);
			Rectf32 xBounds{ glyphRect.left,glyphRect.top,glyphRect.width,glyphRect.height };
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
				if (underlined && (curChar == L'\n')) {
					const f32 top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
					const f32 bottom = top + std::floor(underlineThickness + 0.5f);

					m_vertices.append( vector2df(0, top), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(x, top), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(0, bottom), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(0, bottom), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(x, top), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(x, bottom), m_color, vector2df(1, 1) );
				}

				// If we're using the strike through style and there's a new line, draw a line across all characters
				if (strikeThrough && (curChar == L'\n')) {
					const f32 top{ std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f) };
					const f32 bottom{ top + std::floor(underlineThickness + 0.5f) };

					m_vertices.append( vector2df(0, top), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(x, top), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(0, bottom), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(0, bottom), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(x, top), m_color, vector2df(1, 1) );
					m_vertices.append( vector2df(x, bottom), m_color, vector2df(1, 1) );
				}

				// Handle special characters
				if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n')) {
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

				const f32 left = glyph.bounds.left;
				const f32 top = glyph.bounds.top;
				const f32 right = glyph.bounds.left + glyph.bounds.width;
				const f32 bottom = glyph.bounds.top + glyph.bounds.height;

				const f32 u1 = static_cast<f32>(glyph.textureRect.left);
				const f32 v1 = static_cast<f32>(glyph.textureRect.top);
				const f32 u2 = static_cast<f32>(glyph.textureRect.left + glyph.textureRect.width);
				const f32 v2 = static_cast<f32>(glyph.textureRect.top + glyph.textureRect.height);

				// Add a quad for the current character
				m_vertices.append( vector2df(x + left - italic * top, y + top), m_color, vector2df(u1, v1) );
				m_vertices.append( vector2df(x + right - italic * top, y + top), m_color, vector2df(u2, v1) );
				m_vertices.append( vector2df(x + left - italic * bottom, y + bottom), m_color, vector2df(u1, v2) );
				m_vertices.append( vector2df(x + left - italic * bottom, y + bottom), m_color, vector2df(u1, v2) );
				m_vertices.append( vector2df(x + right - italic * top, y + top), m_color, vector2df(u2, v1) );
				m_vertices.append( vector2df(x + right - italic * bottom, y + bottom), m_color, vector2df(u2, v2) );

				// Update the current bounds
				minX = std::min(minX, x + left - italic * bottom);
				maxX = std::max(maxX, x + right - italic * top);
				minY = std::min(minY, y + top);
				maxY = std::max(maxY, y + bottom);

				// Advance to the next character
				x += glyph.advance;
			}

			// If we're using the underlined style, add the last line
			if (underlined) {
				const f32 top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
				const f32 bottom = top + std::floor(underlineThickness + 0.5f);

				m_vertices.append( vector2df(0, top), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(x, top), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(0, bottom), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(0, bottom), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(x, top), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(x, bottom), m_color, vector2df(1, 1) );
			}

			// If we're using the strike through style, add the last line across all characters
			if (strikeThrough) {
				const f32 top = std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f);
				const f32 bottom = top + std::floor(underlineThickness + 0.5f);

				m_vertices.append( vector2df(0, top), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(x, top), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(0, bottom), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(0, bottom), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(x, top), m_color, vector2df(1, 1) );
				m_vertices.append( vector2df(x, bottom), m_color, vector2df(1, 1) );
			}

			// Update the bounding rectangle
			m_bounds.left = minX;
			m_bounds.top = minY;
			m_bounds.width = maxX - minX;
			m_bounds.height = maxY - minY;
		}

		void NodeText::setPositionWithAlignment(const vector2df &pos, Alignment alignment)
		{
			switch (alignment)
			{
			default:
			case Alignment::Left:
				setPosition(pos);
				break;
			case Alignment::Center:
				setPosition({ pos.x - (getLocalBounds().width / 2.0f), pos.y - (getLocalBounds().height / 2.0f) });
				break;
			case Alignment::Right:
				setPosition({ pos.x - (getLocalBounds().width), pos.y - (getLocalBounds().height) });
				break;
			}
		}

		void NodeText::setPositionWithAlignmentX(const float x, Alignment alignment /*= Alignment::Left*/)
		{
			const vector2df position(getPosition());
			switch (alignment)
			{
			default:
			case Alignment::Left:
				setPosition(vector2df{ x, position.y });
				break;
			case Alignment::Center:
			{
				auto a = vector2df{ x - (getLocalBounds().width / 2.0f), position.y };
				setPosition({ x - (getLocalBounds().width / 2.0f), position.y });
			}
			break;
			case Alignment::Right:
				setPosition({ x - (getLocalBounds().width), position.y });
				break;
			}
		}

		void NodeText::setPositionWithAlignmentY(const float y, Alignment alignment /*= Alignment::Left*/)
		{
			const vector2df position(getPosition());
			switch (alignment)
			{
			default:
			case Alignment::Left:
				setPosition({ position.x, y });
				break;
			case Alignment::Center:
				setPosition({ position.x, y - (getLocalBounds().height / 2.0f) });
				break;
			case Alignment::Right:
				setPosition({ position.x, y - (getLocalBounds().height) });
				break;
			}
		}

		void NodeText::setAlignment(Alignment alignment)
		{
			setPositionWithAlignment(getPosition(), alignment);
		}

	}
}
