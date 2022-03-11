#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/render/renderizables.hpp>

#include "resources/font_utils.hpp"

#include <haf/include/resources/ifont.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/render/vertex_array.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include <haf/include/scene/scenenode_cast.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf::types;

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

SceneNodeText::SceneNodeText(types::rptr<SceneNode> parent, str name) :
    BaseClass{parent, std::move(name)}
{
    inner_transformation_ = addTransformation();
}

void SceneNodeText::onCreated()
{
    setBaseScaleForCurrentView();
}

void SceneNodeText::update()
{
    // TODO: Delete
    auto const& current_text2{prop<SceneNodeTextProperties>().prop<Text>()()};

    if (current_text2 == "2")
    {
        int a = 0;
        (void)(a);
    }

    auto& pr = prop<SceneNodeTextProperties>();
    res::FontUtils const font_utils{pr.get<Font>().get()};
    auto const textSize = pr.get<Font>() != nullptr
        ? font_utils.textSize(pr.get<Text>())
        : Rectf32{};

    if (pr.hasChanged<Font>() || pr.hasChanged<Text>() ||
        pr.hasChanged<BaseScale>())
    {
        pr.readResetHasChanged<BaseScale>();
        pr.setChanged<AlignmentSize>();
        pr.readResetHasChanged<Font>();
        pr.readResetHasChanged<Text>();

        // TODO: Delete
        auto a = pr.get<Font>();
        (void)a;

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

            auto const& current_text{pr.get<Text>()};

            for (auto curChar : current_text)
            {
                types::sptr<RenderizableSceneNode> letterNode;
                // In case we already have a node containing the letter,
                // reuse it. If not, create a new one.
                if (counter < old_counter)
                {
                    letterNode =
                        std::dynamic_pointer_cast<RenderizableSceneNode>(
                            sceneNodes()[counter]);
                }
                else
                {
                    letterNode = createSceneNode<RenderizableSceneNode>(
                        "text_" + str::to_str(counter));
                    letterNode->renderizableBuilder()
                        .name("text_" + str::to_str(counter))
                        .figType(render::FigType_t::Sprite)
                        .create();
                }

                {
                    Rectf32 letterBox{boxes[indexChar++]};
                    if (prop<BaseScale>()() != vector2df{0.0F, 0.0F})
                    {
                        letterBox.scale(prop<BaseScale>()());
                    }
                    letterNode->prop<Position>().set(letterBox.leftTop() +
                                                     letterBox.size() / 2.0F);
                    letterNode->node()->prop<render::ColorProperty>().set(
                        text_color);
                    letterNode->prop<Scale>().set(vector2df{letterBox.size()});

                    ++counter;
                    Rectf32 const textureUV{font->getTextureBounds(curChar)};
                    letterNode->node()->setTextureAndTextureRectFromTextureSize(
                        texture, textureUV);

                    // Update the current bounds
                    {
                        using namespace std;
                        bounds =
                            Rectf32{min(bounds.left, letterBox.left),
                                    min(bounds.top, letterBox.top),
                                    max(bounds.right(), letterBox.right()),
                                    max(bounds.bottom(), letterBox.bottom())};
                    }
                }

                // Advance to the next character
                x += font->getAdvance(curChar);
            }

            // Remove the unused letters.
            // Get the current total size of the vector of scene nodes.
            auto const scene_nodes_size{sceneNodes().size()};
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

            // Force reposition if text changed
            pr.setChanged<AlignmentSize>();

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
        Color const& text_color{pr.get<TextColor>()};

        for_each_sceneNode_as<RenderizableSceneNode>(
            [&text_color](types::sptr<RenderizableSceneNode> const& sNode) {
                sNode->node()->prop<render::ColorProperty>() = text_color;
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
            // TODO: Reenable alignment Y
            /*
            updateAlignmentY(
                getTransformation(inner_transformation_).prop<Position>(),
                prop<AlignmentY>().get(), textSize.height,
                pr.get<AlignmentSize>());
                */
        }
    }
}

void SceneNodeText::setBaseScaleForCurrentView()
{
    prop<BaseScale>() = ancestor<Scene>()->cameraComponent()->view().size() /
        // TODO: Here we have the screen size. Find a way to generalize.
        vector2df{800.0F, 600.0F};
}

}  // namespace haf::scene::nodes
