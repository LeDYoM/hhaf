#include "nodetext.hpp"

#include <lib/scene/ttfont.hpp>
#include <lib/scene/texture.hpp>

#include <mtypes/include/log.hpp>

#include <cmath>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			NodeText::NodeText(SceneNode * const parent, const str & name)
				: Renderizable{ parent, name, Triangles, 0 }
			{
				font.setCallback([this]() { m_geometryNeedsUpdate = true; });
				text.setCallback([this]() { m_geometryNeedsUpdate = true; });
				characterSize.setCallback([this]() { m_geometryNeedsUpdate = true; });
				alignmentX.setCallback([this]() { m_geometryNeedsUpdate = true; });
				alignmentY.setCallback([this]() { m_geometryNeedsUpdate = true; });
				alignmentBox.setCallback([this]() { m_geometryNeedsUpdate = true; });
			}

			void NodeText::updateGeometry()
			{
				if (m_geometryNeedsUpdate) {
					BasicVertexArray &vertices{ m_vertices.verticesArray() };

					m_vertices.bounds = Rectf32{};
					vertices.clear();

					if (!font() || text().empty()) {
						return;
					}

					const u32 currentCharacterSize{ characterSize() };
					const Rectf32 glyphRect{ font()->getGlyph(L'x', currentCharacterSize, false, 0).bounds };
					const f32 vspace{ font()->getLineSpacing(currentCharacterSize) };

					f32 x{ 0.f };
					f32 y{ static_cast<f32>(currentCharacterSize) };

					// Create one quad for each character
					f32 minX{ y }; // static_cast<f32>(characterSize());
					f32 minY{ y }; // static_cast<f32>(characterSize());
					f32 maxX{ 0.f };
					f32 maxY{ 0.f };
					u32 prevChar{ 0 };
					for (auto&& curChar : text())
					{
						// Apply the kerning offset
						x += font()->getKerning(prevChar, curChar, currentCharacterSize);
						prevChar = curChar;

						// Handle special characters
						if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n')) {
							using namespace std;
							// Update the current bounds (min coordinates)
							minX = min(minX, x);
							minY = min(minY, y);
							const f32 hspace{ font()->getGlyph(L' ', currentCharacterSize, false, 0).advance };

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
							const TTGlyph glyph{ font()->getGlyph(curChar, currentCharacterSize, false, 0) };
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
					m_vertices.bounds = { minX, minY, maxX - minX, maxY - minY };
					texture = font()->getTexture(currentCharacterSize);
					updateAlignmentX();
					updateAlignmentY();
					m_geometryNeedsUpdate = false;
					m_colorNeedsUpdate = true;
				}

				if (m_colorNeedsUpdate) {
					color.update();
					m_colorNeedsUpdate = false;
				}
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
