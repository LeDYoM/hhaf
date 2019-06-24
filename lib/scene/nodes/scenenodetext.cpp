#include "scenenodetext.hpp"

#include <lib/include/resources/ifont.hpp>
#include <lib/resources/texture.hpp>
#include <lib/include/liblog.hpp>

#include <lib/scene/vertexarray.hpp>
#include <lib/scene/scenenodetypes.hpp>

// Temp
#include <cmath>

namespace lib::scene::nodes
{
    SceneNodeText::SceneNodeText(SceneNode * const parent, const str & name)
        : SceneNode{ parent, name } //, Triangles, 0 }
    {
    }

    SceneNodeText::~SceneNodeText() = default;

    void SceneNodeText::update()
    {
        BaseClass::update();

        // If the font or the text changed, recreate the children nodes.
        if (font.hasChanged() || text.hasChanged())
        {
            font.resetHasChanged();
            text.resetHasChanged();

            clearSceneNodes();

            if (font() && !(text()().empty()))
            {
                auto texture(font()->getTexture());
                const f32 vspace{ font()->getLineSpacing() };

                f32 x{ 0.f };
                f32 y{ 0.f };

                // Create one quad for each character
                f32 minX{ y };
                f32 minY{ y };
                f32 maxX{ 0.f };
                f32 maxY{ 0.f };
                u32 prevChar{ 0 };

                for (auto&& curChar : text()())
                {
                    // Apply the kerning offset
                    x += font()->getKerning(prevChar, curChar);
                    prevChar = curChar;

                    // Handle special characters
                    if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n')) {
                        using namespace std;
                        // Update the current bounds (min coordinates)
                        minX = min(minX, x);
                        minY = min(minY, y);
                        const f32 hspace{ font()->getAdvance(L' ') };

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
                        const Rectf32 textureUV{ font()->getTextureBounds(curChar) };
                        const Rectf32 letterBox{ font()->getBounds(curChar) + vector2df{ x,y } };

                        auto letterNode(createSceneNode
                                        <RenderizableSceneNode>("text_"+str::to_str(curChar)));
                        letterNode->node()->figType.set(FigType_t::Quad);
                        letterNode->node()->pointCount.set(6U);
                        letterNode->node()->box.set(letterBox);
                        letterNode->node()->setTextureAndTextureRect(texture,
                                    textureUV);

                        // Update the current bounds
                        {
                            using namespace std;
                            minX = min(minX, letterBox.left);
                            maxX = max(maxX, letterBox.right());
                            minY = min(minY, letterBox.top);
                            maxY = max(maxY, letterBox.bottom());
                        }

                        // Advance to the next character
						x += font()->getAdvance(curChar);
                    }
                }

                // Force update color
                textColor.setChanged();
            }
        }

        if (textColor.readResetHasChanged()) 
        {
            const Color &tc{textColor()()};
            sceneNodes().for_each([&tc](const SceneNodeSPtr& sNode) {
                sNode->snCast<RenderizableSceneNode>()->node()->color.set(tc);
            });
        }
    }
}
