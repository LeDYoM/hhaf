#include "nodetext.hpp"

#include <lib/draw/ttfont.hpp>
#include <lib/draw/texture.hpp>

#include <lib/core/log.hpp>

#include <cmath>

namespace lib
{
	namespace draw
	{
		namespace nodes
		{
			NodeText::NodeText(str name) :
				Renderizable{ std::move(name), Triangles, 0 }
			{
				logConstruct("Name: ", this->name());
			}

			NodeText::~NodeText()
			{
				logDestruct("Name: ", name());
			}

			void NodeText::configure()
			{
				configureBase();
				updateGeometry();
			}

			void NodeText::configureBase()
			{
				font.setCallback([this]() { updateGeometry(); });
				text.setCallback([this]() { updateGeometry(); });
				characterSize.setCallback([this]() { updateGeometry(); });
				alignmentX.setCallback([this]() { updateGeometry(); });
				alignmentY.setCallback([this]() {updateGeometry(); });
				alignmentBox.setCallback([this]() {updateGeometry(); });
				Renderizable::configureBase();
			}

			void NodeText::updateGeometry()
			{
				BasicVertexArray &vertices{ m_vertices.verticesArray() };

				m_vertices.setBounds({});
				vertices.clear();

				if (!font() || text().empty()) {
					return;
				}

				const Rectf32 glyphRect{ font()->getGlyph(L'x', characterSize(), false, 0).bounds };
				const f32 hspace{ static_cast<f32>(font()->getGlyph(L' ', characterSize(), false, 0).advance) };
				const f32 vspace{ static_cast<f32>(font()->getLineSpacing(characterSize())) };

				f32 x{ 0.f };
				f32 y{ static_cast<f32>(characterSize()) };

				// Create one quad for each character
				f32 minX{ y }; // static_cast<f32>(characterSize());
				f32 minY{ y }; // static_cast<f32>(characterSize());
				f32 maxX{ 0.f };
				f32 maxY{ 0.f };
				u32 prevChar{ 0 };
				for (const auto curChar : text())
				{
					// Apply the kerning offset
					x += font()->getKerning(prevChar, curChar, characterSize());
					prevChar = curChar;

					// Handle special characters
					if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n')) {
						using namespace std;
						// Update the current bounds (min coordinates)
						minX = min(minX, x);
						minY = min(minY, y);

						switch (curChar)
						{
						case ' ':  x += hspace;        break;
						case '\t': x += hspace * 4;    break;
						case '\n': y += vspace; x = 0; break;
						}

						// Update the current bounds (max coordinates)
						maxX = max(maxX, x);
						maxY = max(maxY, y);
					}
					else {
						// Extract the current glyph's description
						const TTGlyph glyph{ font()->getGlyph(curChar, characterSize(), false, 0) };
						const Rectf32 glyphbound{ glyph.bounds };
						const Rectf32 glyphTextureRect{ glyph.textureBounds };

						const f32 u1 = static_cast<f32>(glyphTextureRect.left);
						const f32 v1 = static_cast<f32>(glyphTextureRect.top);
						const f32 u2 = static_cast<f32>(glyphTextureRect.left + glyphTextureRect.width);
						const f32 v2 = static_cast<f32>(glyphTextureRect.top + glyphTextureRect.height);

						const f32 gleft{ x + glyphbound.left };
						const f32 gright{ x + glyphbound.right() };
						const f32 gtop{ y + glyphbound.top };
						const f32 gbottom{ y + glyphbound.bottom() };
						// Add a quad for the current character
						vertices.emplace_back(vector2df{ gleft,  gtop }, vector2df{ u1, v1 });
						vertices.emplace_back(vector2df{ gright, gtop }, vector2df{ u2, v1 });
						vertices.emplace_back(vector2df{ gleft,  gbottom }, vector2df{ u1, v2 });
						vertices.emplace_back(vector2df{ gleft,  gbottom }, vector2df{ u1, v2 });
						vertices.emplace_back(vector2df{ gright, gtop }, vector2df{ u2, v1 });
						vertices.emplace_back(vector2df{ gright, gbottom }, vector2df{ u2, v2 });

						// Update the current bounds
						using namespace std;
						minX = min(minX, gleft);
						maxX = max(maxX, gright);
						minY = min(minY, gtop);
						maxY = max(maxY, gbottom);

						// Advance to the next character
						x += glyph.advance;
					}
				}

				// Update the bounding rectangle
				m_vertices.setBounds({ minX, minY, maxX - minX, maxY - minY });
				texture.set(msptr<Texture>(font()->getTexture(characterSize())));
				color.update();
				updateAlignmentX();
				updateAlignmentY();
			}

			void NodeText::updateAlignmentX()
			{
				// To be called only after text set
				switch (alignmentX())
				{
				default:
				case AlignmentX::Left:
					m_vertices.moveX(alignmentBox().left);
					break;
				case AlignmentX::Center:
				{
					const auto &abox{ alignmentBox() };
					m_vertices.moveX(abox.left + (abox.width / 2.f) - (bounds().width / 2));
				}
				break;
				case AlignmentX::Right:
					m_vertices.moveX(alignmentBox().right() - bounds().right());
					break;
				}
			}

			void NodeText::updateAlignmentY()
			{
				// To be called only after text set
				switch (alignmentY())
				{
				default:
				case AlignmentY::Top:
					m_vertices.moveY(alignmentBox().top);
					break;
				case AlignmentY::Middle:
				{
					const auto &abox{ alignmentBox() };
					m_vertices.moveY(abox.top + (abox.height / 2.f) - (bounds().height / 2));
				}
				break;
				case AlignmentY::Bottom:
					m_vertices.moveY(alignmentBox().bottom() - bounds().bottom());
					break;
				}
			}
		}
	}
}
