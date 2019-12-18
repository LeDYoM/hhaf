#include "scenenodetext.hpp"

#include <lib/include/resources/ifont.hpp>
#include <lib/resources/texture.hpp>
#include <lib/include/liblog.hpp>

#include <lib/scene/vertexarray.hpp>
#include <lib/scene/scenenodetypes.hpp>

// Temp
#include <cmath>

namespace
{
constexpr bool do_logs{false};

template <typename... Args>
constexpr void log_snt(Args &&... args) noexcept
{
    lib::log_info_if<do_logs>(std::forward<Args>(args)...);
}
} // namespace

namespace lib::scene::nodes
{
SceneNodeText::SceneNodeText(SceneNode *const parent, const str &name)
    : SceneNode{parent, name} {}

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

        if (font() && !(text().empty()))
        {
            auto texture(font()->getTexture());

            f32 x{0.f};
            f32 y{0.f};

            // Create one quad for each character
            f32 minX{y};
            f32 minY{y};
            f32 maxX{0.f};
            f32 maxY{0.f};
            u32 prevChar{0};

            log_snt("Text to render: ", text());

            for (auto &&curChar : text())
            {
                log_snt("-----------------------------------------------------------------");
                log_snt("Current char: ", make_str(curChar));
                log_snt("Current x and y: ", x, ",", y);
                log_snt("minX: ", minX, " minY: ,", minY);
                log_snt("maxX: ", maxX, " maxY: ,", maxY);
                log_snt("prevChar: ", make_str(prevChar));
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
                    const f32 hspace{font()->getAdvance(L' ')};

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
                    const Rectf32 textureUV{font()->getTextureBounds(curChar)};
                    Rectf32 letterBox{font()->getBounds(curChar) + vector2df{x, y}};
                    letterBox += vector2df{50.0F, 50.0F};
                    log_snt("textureUV: ", textureUV);
                    log_snt("letterBox: ", letterBox);

                    auto letterNode(createSceneNode<RenderizableSceneNode>("text_" + str::to_str(curChar)));
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
                    log_snt("advance :", font()->getAdvance(curChar));
                }
            }

            // Force update color
            textColor.setChanged();
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

void SceneNodeText::updateAlignmentX(const f32 textSizeX)
{
    f32 newPosX{0.f};

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

    position.set(vector2df{newPosX, position().y});
}

void SceneNodeText::updateAlignmentY(const f32 textSizeY)
{
    f32 newPosY{0.f};

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

    position.set(vector2df{position().x, newPosY});
}

} // namespace lib::scene::nodes
