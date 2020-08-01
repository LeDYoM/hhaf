#include "scenenodetext.hpp"

#include <haf/resources/include/ifont.hpp>
#include <haf/resources/include/itexture.hpp>
#include <hlog/include/hlog.hpp>

#include <haf/scene/include/vertexarray.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>

#include <algorithm>

using namespace mtps;

namespace
{
constexpr bool do_logs{false};

template <typename... Args>
constexpr void log_snt(Args&&... args) noexcept
{
    haf::DisplayLog::info_if<do_logs>(std::forward<Args>(args)...);
}
}  // namespace

namespace haf::scene::nodes
{

SceneNodeText::~SceneNodeText() = default;

void SceneNodeText::update()
{
    BaseClass::update();

    auto& prop = sceneNodeTextProperties();

    // If the font or the text changed, recreate the children nodes.
    if (prop.hasChanged<Font>() || prop.hasChanged<Text>())
    {
        // Force reposition if font changed.
        if (prop.hasChanged<Font>())
        {
            prop.setChanged<AlignmentSize>();
        }
        prop.readResetHasChanged<Font>();
        prop.readResetHasChanged<Text>();

        if (prop.get<Font>() && !(prop.get<Text>().empty()))
        {
            auto font(prop.get<Font>());
            auto texture(prop.get<Font>()->getTexture());

            f32 x{0.F};
            f32 y{0.F};

            // Create one quad for each character
            f32 minX{y};
            f32 minY{y};
            f32 maxX{0.f};
            f32 maxY{0.f};
            u32 prevChar{0U};
            size_type counter{0U};
            size_type old_counter = sceneNodes().size();
            const Color& tc{prop.get<TextColor>()};

            log_snt("Text to render: ", prop.get<Text>());

            for (auto&& curChar : prop.get<Text>())
            {
                log_snt("------------------------------------------------------"
                        "-----------");
                log_snt("Current char: ", make_str(curChar));
                log_snt("Current x and y: ", x, ",", y);
                log_snt("minX: ", minX, " minY: ,", minY);
                log_snt("maxX: ", maxX, " maxY: ,", maxY);
                log_snt("prevChar: ", make_str(prevChar));
                log_snt("kerning: ", font->getKerning(prevChar, curChar));
                // Apply the kerning offset
                x += font->getKerning(prevChar, curChar);
                log_snt("kerning: ", prop.get<Font>()->getKerning(prevChar, curChar));
                // Apply the kerning offset
                x += prop.get<Font>()->getKerning(prevChar, curChar);
                prevChar = curChar;

                // Handle special characters
                if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
                {
                    using namespace std;
                    // Update the current bounds (min coordinates)
                    minX = min(minX, x);
                    minY = min(minY, y);
                    f32 const hspace{font->getAdvance(L' ')};

                    switch (curChar)
                    {
                        case ' ':
                            x += hspace;
                            break;
                        case '\t':
                            x += hspace * 4;
                            break;
                        case '\n':
                            y += font->getLineSpacing();
                            x = 0.0F;
                            y += prop.get<Font>()->getLineSpacing();
                            x = 0;
                            break;
                    }

                    // Update the current bounds (max coordinates)
                    maxX = max(maxX, x);
                    maxY = max(maxY, y);
                }
                else
                {
                    Rectf32 const textureUV{font->getTextureBounds(curChar)};
                    Rectf32 letterBox{font->getBounds(curChar) +
                                      vector2df{x, y}};
                    letterBox += vector2df{50.0F, 50.0F};
                    log_snt("textureUV: ", textureUV);
                    log_snt("letterBox: ", letterBox);

                    sptr<RenderizableSceneNode> letterNode;
                    // In case we already have a node containing the letter,
                    // reuse it. If not, create a new one.
                    if (counter < old_counter)
                    {
                        letterNode =
                            std::dynamic_pointer_cast<RenderizableSceneNode>(
                                sceneNodes()[counter]);
                        letterNode->node()->color.set(tc);
                        letterNode->node()->box.set(letterBox);
                    }
                    else
                    {
                        letterNode = createSceneNode<RenderizableSceneNode>(
                            "text_" + str::to_str(counter));
                        auto builder = letterNode->renderizableBuilder()
                                           .name("text_" + str::to_str(counter))
                                           .figType(FigType_t::Quad)
                                           .box(letterBox)
                                           .color(tc);
                        letterNode->buildNode(builder);
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
                    x += font->getAdvance(curChar);
                    log_snt("advance :", font->getAdvance(curChar));
                }
            }

            // Remove the unused letters.
            // Get the current total size of the vector of scene nodes.
            const auto scene_nodes_size{sceneNodes().size()};
            // Iterate from the last one to one after counter
            // and delete them
            for (size_type index{(scene_nodes_size - 1U)}; index >= counter;
                 --index)
            {
                // Assert we are removing always the last one.
                LogAsserter::log_assert(sceneNodes()[index] ==
                                        *(sceneNodes().end() - 1U));
                removeSceneNode(sceneNodes()[index]);
            }

            // Force reposition if text size changed.
            if (counter != old_counter)
            {
                prop.setChanged<AlignmentSize>();
            }

            // Force update color
            prop.readResetHasChanged<TextColor>();
        }
        else
        {
            clearSceneNodes();
        }
    }

    if (prop.readResetHasChanged<TextColor>())
    {
        Color const& tc{prop.get<TextColor>()};
        sceneNodes().for_each([&tc](const SceneNodeSPtr& sNode) {
            sNode->snCast<RenderizableSceneNode>()->node()->color.set(tc);
        });
    }

    bool const as_rr_hasChanged{prop.readResetHasChanged<AlignmentSize>()};
//    bool const align_x{prop.readResetHasChanged<AlignmentX>()};
//    bool const align_y{prop.readResetHasChanged<AlignmentY>()};

    if (as_rr_hasChanged || prop.readResetHasChanged<AlignmentX>())
    {
        updateAlignmentX(prop.get<Font>()->textSize(prop.get<Text>()).x);
    }

    if (as_rr_hasChanged || prop.readResetHasChanged<AlignmentY>())
    {
        updateAlignmentY(prop.get<Font>()->textSize(prop.get<Text>()).y);
    }
}

void SceneNodeText::updateAlignmentX(const f32 textSizeX)
{
    f32 newPosX{0.f};

    switch (sceneNodeTextProperties().get<AlignmentX>())
    {
        default:
        case AlignmentXModes::Left:
            break;
        case AlignmentXModes::Center:
            newPosX = (sceneNodeTextProperties().get<AlignmentSize>().x / 2) -
                (textSizeX / 2);
            break;
        case AlignmentXModes::Right:
            newPosX =
                sceneNodeTextProperties().get<AlignmentSize>().x - textSizeX;
            break;
    }

    position.set(vector2df{newPosX, position().y});
}

void SceneNodeText::updateAlignmentY(const f32 textSizeY)
{
    f32 newPosY{0.f};

    switch (sceneNodeTextProperties().get<AlignmentY>())
    {
        default:
        case AlignmentYModes::Top:
            break;
        case AlignmentYModes::Middle:
            newPosY = (sceneNodeTextProperties().get<AlignmentSize>().y / 2) -
                (textSizeY / 2);
            break;
        case AlignmentYModes::Bottom:
            newPosY =
                sceneNodeTextProperties().get<AlignmentSize>().y - textSizeY;
            break;
    }

    position.set(vector2df{position().x, newPosY});
}

}  // namespace haf::scene::nodes
