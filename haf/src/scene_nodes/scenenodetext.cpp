#include <haf/include/scene_nodes/scenenodetext.hpp>
#include <haf/include/render/renderizables.hpp>

#include "resources/font_utils.hpp"

#include <haf/include/resources/ifont.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/render/vertexarray.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include <haf/include/scene/scenenode_cast.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene::nodes
{

namespace
{
inline void updateAlignmentX(
    PropertyState<vector2df, Position>& position,
    AlignmentX::value_type const alignmentX,
    f32 const textSizeX,
    AlignmentSize::value_type const& alignmentSize) noexcept
{
    f32 newPosX{0.f};

    switch (alignmentX)
    {
        default:
        case AlignmentXModes::Left:
            break;
        case AlignmentXModes::Center:
            newPosX = (alignmentSize.x / 2) - (textSizeX / 2);
            break;
        case AlignmentXModes::Right:
            newPosX = (alignmentSize.x - textSizeX);
            break;
    }

    position.set(vector2df{newPosX, position.get().y});
}

inline void updateAlignmentY(
    PropertyState<vector2df, Position>& position,
    AlignmentY::value_type const alignmentY,
    f32 const textSizeY,
    AlignmentSize::value_type const& alignmentSize) noexcept
{
    f32 newPosY{0.f};

    switch (alignmentY)
    {
        default:
        case AlignmentYModes::Top:
            break;
        case AlignmentYModes::Middle:
            newPosY = (alignmentSize.y / 2) - (textSizeY / 2);
            break;
        case AlignmentYModes::Bottom:
            newPosY = alignmentSize.y - textSizeY;
            break;
    }

    position.set(vector2df{position.get().x, newPosY});
}
}  // namespace

SceneNodeText::SceneNodeText(rptr<SceneNode> parent, str name) :
    BaseClass{parent, std::move(name)}
{
    inner_transformation_ = addTransformation();
}

void SceneNodeText::update()
{
    BaseClass::update();

    auto& pr = prop<SceneNodeTextProperties>();
    res::FontUtils const font_utils{pr.get<Font>().get()};
    auto const textSize = pr.get<Font>() != nullptr
        ? font_utils.textSize(pr.get<Text>())
        : Rectf32{};

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
            using counter_t = decltype(sceneNodes().size());

            Rectf32 bounds{x, y, 0.0F, 0.0F};
            counter_t counter{0U};
            counter_t const old_counter{sceneNodes().size()};
            auto const& text_color{pr.get<TextColor>()};
            auto const boxes{font_utils.getTextBoxes(pr.get<Text>())};
            size_type indexChar{0U};

            for (auto curChar : pr.get<Text>())
            {
                Rectf32 letterBox{font->getBounds(curChar) + vector2df{x, y}};
                letterBox = boxes[indexChar++];

                sptr<RenderizableSceneNode> letterNode;
                // In case we already have a node containing the letter,
                // reuse it. If not, create a new one.
                if (counter < old_counter)
                {
                    letterNode =
                        std::dynamic_pointer_cast<RenderizableSceneNode>(
                            sceneNodes()[counter]);
                    letterNode->node()->color.set(text_color);
                    letterNode->node()->box.set(letterBox);
                }
                else
                {
                    letterNode = createSceneNode<RenderizableSceneNode>(
                        "text_" + str::to_str(counter));
                    auto builder = letterNode->renderizableBuilder()
                                       .name("text_" + str::to_str(counter))
                                       .figType(render::FigType_t::Quad)
                                       .box(letterBox)
                                       .color(text_color);
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
        sceneNodes().for_each([&tc](SceneNodeSPtr const& sNode) {
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
            updateAlignmentX(
                getTransformation(inner_transformation_).prop<Position>(),
                prop<AlignmentX>().get(), textSize.width,
                pr.get<AlignmentSize>());
        }

        if (as_rr_hasChanged || align_y)
        {
            updateAlignmentY(
                getTransformation(inner_transformation_).prop<Position>(),
                prop<AlignmentY>().get(), textSize.height,
                pr.get<AlignmentSize>());
        }
    }
}

}  // namespace haf::scene::nodes
