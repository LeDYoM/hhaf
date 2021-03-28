#include <haf/scene_nodes/include/scenenodetext.hpp>

#include <haf/resources/include/ifont.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/i_include/font_utils.hpp>
#include <hlog/include/hlog.hpp>

#include <haf/render/include/vertexarray.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>

using namespace htps;

namespace haf::scene::nodes
{

void SceneNodeText::update()
{
    BaseClass::update();

    auto& pr = prop<SceneNodeTextProperties>();
    res::FontUtils const font_utils{pr.get<Font>().get()};
    auto const textSize = font_utils.textSize(pr.get<Text>());

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
            Rectf32 bounds{x, y, 0.0F, 0.0F};
            size_type counter{0U};
            auto const old_counter{sceneNodes().size()};
            const Color& tc{pr.get<TextColor>()};
            auto const boxes = font_utils.getTextBoxes(pr.get<Text>());
            size_type indexChar{0U};

            for (auto curChar : pr.get<Text>())
            {
                Rectf32 letterBox{font->getBounds(curChar) + vector2df{x, y}};
                letterBox += vector2df{0.0F, 50.0F};
                letterBox = boxes[indexChar++];

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
                Rectf32 const textureUV{font->getTextureBounds(curChar)};
                letterNode->node()->setTextureAndTextureRect(texture,
                                                             textureUV);

                // Update the current bounds
                {
                    using namespace std;
                    bounds = Rectf32{min(bounds.left, letterBox.left),
                                     min(bounds.top, letterBox.top),
                                     max(bounds.right(), letterBox.right()),
                                     max(bounds.bottom(), letterBox.bottom())};
                }

                // Advance to the next character
                x += font->getAdvance(curChar);
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

    if (pr.get<Font>() != nullptr)
    {
        bool const as_rr_hasChanged{pr.readResetHasChanged<AlignmentSize>()};
        bool const align_x{pr.readResetHasChanged<AlignmentX>()};
        bool const align_y{pr.readResetHasChanged<AlignmentY>()};

        if (as_rr_hasChanged || align_x)
        {
            updateAlignmentX(textSize.width);
        }

        if (as_rr_hasChanged || align_y)
        {
            updateAlignmentY(textSize.height);
        }
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
