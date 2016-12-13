#include "vertexarray.hpp"

#include "font.hpp"
#include <lib/core/window.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		constexpr VertexArray::VertexArray() noexcept
			: m_vertices{}, m_primitiveType{ PrimitiveType::Points } {}


		VertexArray::VertexArray(const PrimitiveType type, const std::size_t vertexCount) noexcept
			: m_vertices{ vertexCount }, m_primitiveType{ type } {}

		Rectf32 VertexArray::generateQuad(const vector2df & size, const Color &globalColor)
		{
			constexpr u32 nPoints = 4;
			constexpr u32 nVertex = nPoints + 2;

			m_vertices.resize(nVertex); // + 2 for center and repeated first point
			m_vertices[1].position = vector2df(0, 0);
			m_vertices[1].color = globalColor;
			m_vertices[2].position = vector2df(size.x, 0);
			m_vertices[2].color = globalColor;
			m_vertices[3].position = vector2df(size.x, size.y);
			m_vertices[3].color = globalColor;
			m_vertices[4].position = vector2df(0, size.y);
			m_vertices[4].color = globalColor;

			// Update the bounding rectangle
			m_vertices[5] = m_vertices[1]; // so that the result of getBounds() is correct
			m_vertices[5].color = globalColor;
			const Rectf32 bounds = getBounds();
			// Compute the center and make it the first vertex
			m_vertices[0].position.x = bounds.width / 2;
			m_vertices[0].position.y = bounds.height / 2;

			return bounds;
		}

		template <typename T>
		constexpr T PIConstant = 3.14159265358979323846;
		template <typename T>
		constexpr T PID2Constant = 3.14159265358979323846 / static_cast<T>(2);

		Rectf32 VertexArray::generateShape(const vector2df & size, const Color &globalColor, const u32 granularity)
		{
			const u32 nPoints(granularity);
			const u32 nVertex = nPoints + 2;

			m_vertices.resize(nVertex); // + 2 for center and repeated first point
			const vector2df radius{ size / 2.0f };
			const f64 baseAngle((2 * PIConstant<f64>) / granularity);
			for (std::size_t i = 0; i < nPoints; ++i)
			{
				const f64 angle = (i*baseAngle) - (PID2Constant<f64>);
				const vector2dd r{ std::cos(angle) * radius.x, std::sin(angle) * radius.y };
				m_vertices[i + 1].position = vector2df{ static_cast<f32>(radius.x + r.x), static_cast<f32>(radius.y + r.y) };
				m_vertices[i + 1].color = globalColor;
			}

			m_vertices[nPoints + 1].position = m_vertices[1].position;
			m_vertices[nPoints + 1].color = globalColor;

			// Update the bounding rectangle
			m_vertices[0] = m_vertices[1]; // so that the result of getBounds() is correct
			m_vertices[0].color = globalColor;
			const Rectf32 bounds = getBounds();
			// Compute the center and make it the first vertex
			m_vertices[0].position.x = bounds.width / 2;
			m_vertices[0].position.y = bounds.height / 2;

			return bounds;
		}

		Rectf32 VertexArray::generateText(const sptr<Font> &font, std::string str, const Color &globalColor,
			const u32 characterSize, const bool bold, const bool underlined, const bool strikeThrough, const bool isItalic)
		{
			// Clear the previous geometry
			m_vertices.clear();
			Rectf32 bounds{};

			// No font: nothing to draw
			if (!font)
				return bounds;

			// No text: nothing to draw
			if (str.empty())
				return bounds;

			// Compute values related to the text style
			const f32 italic = (isItalic) ? 0.208f : 0.f; // 12 degrees
			const f32 underlineOffset{ font->getUnderlinePosition(characterSize) };
			const f32 underlineThickness{ font->getUnderlineThickness(characterSize) };

			// Compute the location of the strike through dynamically
			// We use the center point of the lowercase 'x' glyph as the reference
			// We reuse the underline thickness as the thickness of the strike through as well
			sf::FloatRect glyphRect(font->getGlyph(L'x', characterSize, bold).bounds);
			Rectf32 xBounds{ glyphRect.left,glyphRect.top,glyphRect.width,glyphRect.height };
			const f32 strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

			// Precompute the variables needed by the algorithm
			const f32 hspace = static_cast<float>(font->getGlyph(L' ', characterSize, bold).advance);
			const f32 vspace = static_cast<float>(font->getLineSpacing(characterSize));
			f32 x = 0.f;
			f32 y = static_cast<f32>(characterSize);

			// Create one quad for each character
			f32 minX = static_cast<f32>(characterSize);
			f32 minY = static_cast<f32>(characterSize);
			f32 maxX = 0.f;
			f32 maxY = 0.f;
			sf::Uint32 prevChar = 0;
			for (const auto curChar : str)
			{
				// Apply the kerning offset
				x += static_cast<f32>(font->getKerning(prevChar, curChar, characterSize));
				prevChar = curChar;

				// If we're using the underlined style and there's a new line, draw a line
				if (underlined && (curChar == L'\n')) {
					const f32 top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
					const f32 bottom = top + std::floor(underlineThickness + 0.5f);

					m_vertices.emplace_back(vector2df(0, top), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(x, top), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(0, bottom), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(0, bottom), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(x, top), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(x, bottom), globalColor, vector2df(1, 1));
				}

				// If we're using the strike through style and there's a new line, draw a line across all characters
				if (strikeThrough && (curChar == L'\n')) {
					const f32 top{ std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f) };
					const f32 bottom{ top + std::floor(underlineThickness + 0.5f) };

					m_vertices.emplace_back(vector2df(0, top), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(x, top), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(0, bottom), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(0, bottom), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(x, top), globalColor, vector2df(1, 1));
					m_vertices.emplace_back(vector2df(x, bottom), globalColor, vector2df(1, 1));
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
				const sf::Glyph& glyph = font->getGlyph(curChar, characterSize, bold);

				const f32 left = glyph.bounds.left;
				const f32 top = glyph.bounds.top;
				const f32 right = glyph.bounds.left + glyph.bounds.width;
				const f32 bottom = glyph.bounds.top + glyph.bounds.height;

				const f32 u1 = static_cast<f32>(glyph.textureRect.left);
				const f32 v1 = static_cast<f32>(glyph.textureRect.top);
				const f32 u2 = static_cast<f32>(glyph.textureRect.left + glyph.textureRect.width);
				const f32 v2 = static_cast<f32>(glyph.textureRect.top + glyph.textureRect.height);

				// Add a quad for the current character
				m_vertices.emplace_back(vector2df(x + left - (italic * top), y + top), globalColor, vector2df(u1, v1));
				m_vertices.emplace_back(vector2df(x + right - (italic * top), y + top), globalColor, vector2df(u2, v1));
				m_vertices.emplace_back(vector2df(x + left - (italic * bottom), y + bottom), globalColor, vector2df(u1, v2));
				m_vertices.emplace_back(vector2df(x + left - (italic * bottom), y + bottom), globalColor, vector2df(u1, v2));
				m_vertices.emplace_back(vector2df(x + right - italic * top, y + top), globalColor, vector2df(u2, v1));
				m_vertices.emplace_back(vector2df(x + right - italic * bottom, y + bottom), globalColor, vector2df(u2, v2));

				// Update the current bounds
				minX = std::min(minX, x + left - (italic * bottom));
				maxX = std::max(maxX, x + right - (italic * top));
				minY = std::min(minY, y + top);
				maxY = std::max(maxY, y + bottom);

				// Advance to the next character
				x += glyph.advance;
			}

			// If we're using the underlined style, add the last line
			if (underlined) {
				const f32 top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
				const f32 bottom = top + std::floor(underlineThickness + 0.5f);

				m_vertices.emplace_back(vector2df(0, top), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(x, top), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(0, bottom), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(0, bottom), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(x, top), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(x, bottom), globalColor, vector2df(1, 1));
			}

			// If we're using the strike through style, add the last line across all characters
			if (strikeThrough) {
				const f32 top = std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f);
				const f32 bottom = top + std::floor(underlineThickness + 0.5f);

				m_vertices.emplace_back(vector2df(0, top), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(x, top), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(0, bottom), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(0, bottom), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(x, top), globalColor, vector2df(1, 1));
				m_vertices.emplace_back(vector2df(x, bottom), globalColor, vector2df(1, 1));
			}

			// Update the bounding rectangle
			bounds.left = minX;
			bounds.top = minY;
			bounds.width = maxX - minX;
			bounds.height = maxY - minY;

			return bounds;
		}

		void VertexArray::for_each_vertex(std::function<void(Vertex&)>&& f)
		{
			std::for_each(m_vertices.begin(), m_vertices.end(), std::move(f));
		}

		Rectf32 VertexArray::getBounds() const
		{
			if (!m_vertices.empty()) {
				f32 left = m_vertices[0].position.x;
				f32 top = m_vertices[0].position.y;
				f32 right = m_vertices[0].position.x;
				f32 bottom = m_vertices[0].position.y;

				for (const auto& v : m_vertices)
				{
					const vector2df &position{ v.position };

					// Update left and right
					if (position.x < left)
						left = position.x;
					else if (position.x > right)
						right = position.x;

					// Update top and bottom
					if (position.y < top)
						top = position.y;
					else if (position.y > bottom)
						bottom = position.y;
				}

				return Rectf32{ left, top, right - left, bottom - top };
			}
			else {
				return Rectf32{};
			}
		}

		void VertexArray::draw() const
		{
			host().parentWindow().draw((const sf::Vertex*)m_vertices.data(), m_vertices.size(), static_cast<sf::PrimitiveType>(m_primitiveType),
				host().rStates().internalStates());
		}

		void VertexArray::setColor(const Color color)
		{
			if (!m_vertices.empty()) for (auto &v : m_vertices) v.color = color;
		}
	}
}
