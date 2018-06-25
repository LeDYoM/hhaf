#include "scenenodetext.hpp"

#include <lib/scene/ttfont.hpp>
#include <lib/scene/texture.hpp>
#include <lib/include/core/log.hpp>


#include <cmath>

namespace lib::scene::nodes
{
    SceneNodeText::SceneNodeText(SceneNode * const parent, const str & name)
        : SceneNode{ parent, name } //, Triangles, 0 }
    {
    }

    /*
    void SceneNodeText::updateGeometry()
    {
        if (ps_readResetHasChanged(font, characterSize)) {
            if (font() && characterSize() > 0) {
                font()->ensureLoadASCIIGlyps(characterSize());
                texture = font()->getTexture(characterSize());
                text.setChanged();
            }
        }

        if (ps_readResetHasChanged(text, alignmentBox, alignmentX, alignmentY)) {
            BasicVertexArray &vertices{ m_vertices.verticesArray() };

            m_vertices.bounds = Rectf32{};
            vertices.clear();

            if (!font() || text().empty()) {
                return;
            }

            const u32 currentCharacterSize{ characterSize() };
            const Rectf32 glyphRect{ font()->getGlyph(L'x', currentCharacterSize).bounds };
            const f32 vspace{ font()->getLineSpacing(currentCharacterSize) };

            f32 x{ 0.f };
            f32 y{ static_cast<f32>(currentCharacterSize) };

            // Create one quad for each character
            f32 minX{ y };
            f32 minY{ y };
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
                    const f32 hspace{ font()->getGlyph(L' ', currentCharacterSize).advance };

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
                else
                {
                    const TTGlyph glyph{ font()->getGlyph(curChar, currentCharacterSize) };
                    const Rectf32 textureUV{ glyph.textureBounds};
                    const Rectf32 letterBox{ glyph.bounds + vector2df{ x,y } };

                    // Add a quad for the current character
                    vertices.emplace_back(vector2df{ letterBox.left,    letterBox.top }, vector2df{ textureUV.left, textureUV.top });
                    vertices.emplace_back(vector2df{ letterBox.right(), letterBox.top }, vector2df{ textureUV.right(), textureUV.top });
                    vertices.emplace_back(vector2df{ letterBox.left,    letterBox.bottom() }, vector2df{ textureUV.left, textureUV.bottom() });
                    vertices.emplace_back(vector2df{ letterBox.left,    letterBox.bottom() }, vector2df{ textureUV.left, textureUV.bottom() });
                    vertices.emplace_back(vector2df{ letterBox.right(), letterBox.top }, vector2df{ textureUV.right(), textureUV.top });
                    vertices.emplace_back(vector2df{ letterBox.right(), letterBox.bottom() }, vector2df{ textureUV.right(), textureUV.bottom() });

                    // Update the current bounds
                    {
                        using namespace std;
                        minX = min(minX, letterBox.left);
                        maxX = max(maxX, letterBox.right());
                        minY = min(minY, letterBox.top);
                        maxY = max(maxY, letterBox.bottom());
            NodeText        }

                    // Advance to the next character
                    x += glyph.advance;
                }
            }

            // Update the bounding rectangle
            m_vertices.bounds = { minX, minY, maxX - minX, maxY - minY };
            alignmentBox.setChanged();
        }

        const bool ab_rr_hasChanged{ alignmentBox.readResetHasChanged() };

        if (ab_rr_hasChanged || alignmentX.readResetHasChanged())
        {
            updateAlignmentX();
        }

        if (ab_rr_hasChanged || alignmentY.readResetHasChanged())
        {
            updateAlignmentY();
        }
    }
    */

    /*
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
    */
}
