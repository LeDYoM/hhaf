#include "scenenodetext.hpp"

#include <lib/resources/include/ifont.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/include/liblog.hpp>

#include <lib/scene/include/vertexarray.hpp>
#include <lib/scene/include/scenenodetypes.hpp>

#include <algorithm>

namespace
{
constexpr bool do_logs{false};

template <typename... Args>
constexpr void log_snt(Args &&... args) noexcept
{
    lib::DisplayLog::info_if<do_logs>(std::forward<Args>(args)...);
}
} // namespace

namespace lib::scene::nodes
{
SceneNodeText::SceneNodeText(SceneNode *const parent, const mtps::str&name)
    : SceneNode{parent, name} {}

SceneNodeText::~SceneNodeText() = default;

void SceneNodeText::update()
{
    BaseClass::update();

    // If the font or the text changed, recreate the children nodes.
    if (font.hasChanged() || text.hasChanged())
    {
        // Force reposition if font changed.
        if (font.hasChanged())
        {
            alignmentSize.setChanged();
        }
        font.resetHasChanged();
        text.resetHasChanged();

        if (font() && !(text().empty()))
        {
            auto texture(font()->getTexture());

            mtps::f32 x{0.f};
            mtps::f32 y{0.f};

            // Create one quad for each character
            mtps::f32 minX{y};
            mtps::f32 minY{y};
            mtps::f32 maxX{0.f};
            mtps::f32 maxY{0.f};
            mtps::u32 prevChar{0U};
            mtps::size_type counter{0U};
            mtps::size_type old_counter = sceneNodes().size();
            const Color &tc{textColor()};

            log_snt("Text to render: ", text());

            for (auto &&curChar : text())
            {
                log_snt("-----------------------------------------------------------------");
                log_snt("Current char: ", mtps::make_str(curChar));
                log_snt("Current x and y: ", x, ",", y);
                log_snt("minX: ", minX, " minY: ,", minY);
                log_snt("maxX: ", maxX, " maxY: ,", maxY);
                log_snt("prevChar: ", mtps::make_str(prevChar));
                log_snt("kerning: ", font()->getKerning(prevChar, curChar));
                // Apply the kerning offset
                x += font()->getKerning(prevChar, curChar);
                prevChar = curChar;

                // Handle special characters
                if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
                {
                    using namespace std;
                    // Update the current bounds (min coordinates)
                    minX = min(minX, x);
                    minY = min(minY, y);
                    const mtps::f32 hspace{font()->getAdvance(L' ')};

                    switch (curChar)
                    {
                    case ' ':
                        x += hspace;
                        break;
                    case '\t':
                        x += hspace * 4;
                        break;
                    case '\n':
                        y += font()->getLineSpacing();
                        x = 0;
                        break;
                    }

                    // Update the current bounds (max coordinates)
                    maxX = max(maxX, x);
                    maxY = max(maxY, y);
                }
                else
                {
                    const mtps::Rectf32 textureUV{font()->getTextureBounds(curChar)};
                    mtps::Rectf32 letterBox{font()->getBounds(curChar) + mtps::vector2df{x, y}};
                    letterBox += mtps::vector2df{50.0F, 50.0F};
                    log_snt("textureUV: ", textureUV);
                    log_snt("letterBox: ", letterBox);

                    mtps::sptr<RenderizableSceneNode> letterNode;
                    // In case we already have a node containing the letter,
                    // reuse it. If not, create a new one.
                    if (counter < old_counter)
                    {
                        letterNode = std::dynamic_pointer_cast<RenderizableSceneNode>(sceneNodes()[counter]);
                        letterNode->node()->color.set(tc);
                        letterNode->node()->box.set(letterBox);
                    }
                    else
                    {
                        letterNode = createSceneNode<RenderizableSceneNode>(
                            "text_" + mtps::str::to_str(counter),
                            FigType_t::Quad, letterBox, tc);
                    }
                    ++counter;
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
                    log_snt("advance :", font()->getAdvance(curChar));
                }
            }

            // Remove the unused letters.
            // Get the current total size of the vector of scene nodes.
            const auto scene_nodes_size{sceneNodes().size()};
            // Iterate from the last one to one after counter
            // and delete them
            for (mtps::size_type index{(scene_nodes_size - 1U)};
                 index >= counter; --index)
            {
                // Assert we are removing always the last one.
                log_assert(sceneNodes()[index] == *(sceneNodes().end() - 1U));
                removeSceneNode(sceneNodes()[index]);
            }

            // Force reposition if text size changed.
            if (counter != old_counter)
            {
                alignmentSize.setChanged();
            }

            // Force update color
            textColor.resetHasChanged();
        }
        else
        {
            clearSceneNodes();
        }
    }

    if (textColor.readResetHasChanged())
    {
        const Color &tc{textColor()};
        sceneNodes().for_each([&tc](const SceneNodeSPtr &sNode) {
            sNode->snCast<RenderizableSceneNode>()->node()->color.set(tc);
        });
    }

    const bool as_rr_hasChanged{alignmentSize.readResetHasChanged()};

    if (as_rr_hasChanged || alignmentX.readResetHasChanged())
    {
        updateAlignmentX(font()->textSize(text()).x);
    }

    if (as_rr_hasChanged || alignmentY.readResetHasChanged())
    {
        updateAlignmentY(font()->textSize(text()).y);
    }
}

void SceneNodeText::updateAlignmentX(const mtps::f32 textSizeX)
{
    mtps::f32 newPosX{0.f};

    switch (alignmentX())
    {
    default:
    case AlignmentX::Left:
        break;
    case AlignmentX::Center:
        newPosX = (alignmentSize().x / 2) - (textSizeX / 2);
        break;
    case AlignmentX::Right:
        newPosX = alignmentSize().x - textSizeX;
        break;
    }

    position.set(mtps::vector2df{newPosX, position().y});
}

void SceneNodeText::updateAlignmentY(const mtps::f32 textSizeY)
{
    mtps::f32 newPosY{0.f};

    switch (alignmentY())
    {
    default:
    case AlignmentY::Top:
        break;
    case AlignmentY::Middle:
        newPosY = (alignmentSize().y / 2) - (textSizeY / 2);
        break;
    case AlignmentY::Bottom:
        newPosY = alignmentSize().y - textSizeY;
        break;
    }

    position.set(mtps::vector2df{position().x, newPosY});
}

} // namespace lib::scene::nodes
