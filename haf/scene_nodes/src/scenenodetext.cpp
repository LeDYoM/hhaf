#include <haf/scene_nodes/include/scenenodetext.hpp>

#include <haf/resources/include/ifont.hpp>
#include <haf/resources/include/itexture.hpp>
#include <hlog/include/hlog.hpp>

#include <haf/render/include/vertexarray.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>

#include <algorithm>

using namespace mtps;

namespace
{
constexpr bool do_logs{false};

template <typename... Args>
constexpr void log_snt(Args&&... args) noexcept
{
    haf::DisplayLog::info_if_ce<do_logs>(std::forward<Args>(args)...);
}
}  // namespace

namespace haf::scene::nodes
{

SceneNodeText::~SceneNodeText() = default;

void SceneNodeText::update()
{
    BaseClass::update();

    auto& pr = prop<SceneNodeTextProperties>();
    // If the font or the text changed, recreate the children nodes.
    if (pr.hasChanged<Font>() || pr.hasChanged<Text>())
    {
        // Force reposition if font changed.
        if (pr.hasChanged<Font>())
        {
            pr.setChanged<AlignmentSize>();
        }
        pr.readResetHasChanged<Font>();
        pr.readResetHasChanged<Text>();

        if (pr.get<Font>() && !(pr.get<Text>().empty()))
        {
            auto font(pr.get<Font>());
            auto texture(pr.get<Font>()->getTexture());

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
            const Color& tc{pr.get<TextColor>()};

            log_snt("Text to render: ", pr.get<Text>());

            for (auto&& curChar : pr.get<Text>())
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
                log_snt("kerning: ", font->getKerning(prevChar, curChar));
                // Apply the kerning offset
                x += font->getKerning(prevChar, curChar);
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
                            y += font->getLineSpacing();
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
                pr.setChanged<AlignmentSize>();
            }

            // Force update color
            pr.readResetHasChanged<TextColor>();
        }
        else
        {
            clearSceneNodes();
        }
    }

    if (pr.readResetHasChanged<TextColor>())
    {
        Color const& tc{pr.get<TextColor>()};
        sceneNodes().for_each([&tc](const SceneNodeSPtr& sNode) {
            sceneNodeCast<RenderizableSceneNode>(sNode)->node()->color.set(tc);
        });
    }

    bool const as_rr_hasChanged{pr.readResetHasChanged<AlignmentSize>()};
    bool const align_x{pr.readResetHasChanged<AlignmentX>()};
    bool const align_y{pr.readResetHasChanged<AlignmentY>()};

    if (as_rr_hasChanged || align_x)
    {
        updateAlignmentX(pr.get<Font>()->textSize(pr.get<Text>()).x);
    }

    if (as_rr_hasChanged || align_y)
    {
        updateAlignmentY(pr.get<Font>()->textSize(pr.get<Text>()).y);
    }
}

void SceneNodeText::updateAlignmentX(f32 const textSizeX)
{
    f32 newPosX{0.f};

    switch (prop<AlignmentX>().get())
    {
        default:
        case AlignmentXModes::Left:
            break;
        case AlignmentXModes::Center:
            newPosX = (prop<AlignmentSize>().get().x / 2) - (textSizeX / 2);
            break;
        case AlignmentXModes::Right:
            newPosX = (prop<AlignmentSize>().get().x - textSizeX);
            break;
    }

    prop<Position>().set(vector2df{newPosX, prop<Position>().get().y});
}

void SceneNodeText::updateAlignmentY(f32 const textSizeY)
{
    f32 newPosY{0.f};

    switch (prop<AlignmentY>().get())
    {
        default:
        case AlignmentYModes::Top:
            break;
        case AlignmentYModes::Middle:
            newPosY = (prop<AlignmentSize>().get().y / 2) - (textSizeY / 2);
            break;
        case AlignmentYModes::Bottom:
            newPosY = prop<AlignmentSize>().get().y - textSizeY;
            break;
    }

    prop<Position>().set(vector2df{prop<Position>().get().x, newPosY});
}

}  // namespace haf::scene::nodes
