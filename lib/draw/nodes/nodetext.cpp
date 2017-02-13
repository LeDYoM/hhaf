#include "nodetext.hpp"

#include <lib/draw/font.hpp>
#include <lib/draw/texture.hpp>

#include <cmath>

namespace lib
{
	namespace draw
	{
		namespace nodes
		{
			NodeText::NodeText(str_const name, std::string txt, sptr<Font> font_, u32 characterSize_, const Color &color) :
				Renderizable{ std::move(name), nullptr, Triangles, 0, color },
				font{ font_, [this]() { updateGeometry(); } },
				text{ std::move(txt), [this]() { updateGeometry(); } },
				characterSize{ characterSize_, [this]() { updateGeometry(); } }
			{
				logConstruct("Name: ", name);

				updateGeometry();
			}

			NodeText::~NodeText()
			{
				logDestruct("Name: ", name());
			}

			void NodeText::updateGeometry()
			{
				BasicVertexArray &vertices{ m_vertices.verticesArray() };

				m_vertices.setBounds({});
				vertices.clear();

				if (!font() || text().empty())
				{
					return;
				}

				sf::FloatRect glyphRect(font()->getGlyph(L'x', characterSize(), false).bounds);
				Rectf32 xBounds{ glyphRect.left,glyphRect.top,glyphRect.width,glyphRect.height };
				const f32 strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

				const f32 hspace = static_cast<f32>(font()->getGlyph(L' ', characterSize(), false).advance);
				const f32 vspace = static_cast<f32>(font()->getLineSpacing(characterSize()));
				f32 x = 0.f;
				f32 y = static_cast<f32>(characterSize());

				// Create one quad for each character
				f32 minX = static_cast<f32>(characterSize());
				f32 minY = static_cast<f32>(characterSize());
				f32 maxX = 0.f;
				f32 maxY = 0.f;
				u32 prevChar = 0;
				for (const auto curChar : text())
				{
					// Apply the kerning offset
					x += static_cast<f32>(font()->getKerning(prevChar, curChar, characterSize()));
					prevChar = curChar;

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
					}
					else {

						// Extract the current glyph's description
						const sf::Glyph& glyph = font()->getGlyph(curChar, characterSize(), false);

						const f32 left = glyph.bounds.left;
						const f32 top = glyph.bounds.top;
						const f32 right = glyph.bounds.left + glyph.bounds.width;
						const f32 bottom = glyph.bounds.top + glyph.bounds.height;

						const f32 u1 = static_cast<f32>(glyph.textureRect.left);
						const f32 v1 = static_cast<f32>(glyph.textureRect.top);
						const f32 u2 = static_cast<f32>(glyph.textureRect.left + glyph.textureRect.width);
						const f32 v2 = static_cast<f32>(glyph.textureRect.top + glyph.textureRect.height);

						// Add a quad for the current character
						vertices.emplace_back(vector2df(x + left, y + top), vector2df(u1, v1));
						vertices.emplace_back(vector2df(x + right, y + top), vector2df(u2, v1));
						vertices.emplace_back(vector2df(x + left, y + bottom), vector2df(u1, v2));
						vertices.emplace_back(vector2df(x + left, y + bottom), vector2df(u1, v2));
						vertices.emplace_back(vector2df(x + right, y + top), vector2df(u2, v1));
						vertices.emplace_back(vector2df(x + right, y + bottom), vector2df(u2, v2));

						// Update the current bounds
						minX = std::min(minX, x + left);
						maxX = std::max(maxX, x + right);
						minY = std::min(minY, y + top);
						maxY = std::max(maxY, y + bottom);

						// Advance to the next character
						x += glyph.advance;
					}
				}

				// Update the bounding rectangle
				m_vertices.setBounds({ minX, minY, maxX - minX, maxY - minY });
				texture.set(msptr<Texture>(font()->getTexture(characterSize())));
				color.update();
			}
		}
	}
}
