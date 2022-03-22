#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/render/renderizables.hpp>

#include "scene_node_letter.hpp"
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
{}

void SceneNodeText::update()
{
    // TODO: Delete
    auto const& current_text2{prop<SceneNodeTextProperties>().prop<Text>()()};

    if (current_text2 == "1234 ABC abc")
    {
        int a = 0;
        (void)(a);
    }

    auto& pr = prop<SceneNodeTextProperties>();
    res::FontUtils const font_utils{pr.get<Font>().get()};
    if (pr.hasChanged<Font>() || pr.hasChanged<Text>())
    {
        pr.setChanged<AlignmentSize>();
        pr.readResetHasChanged<Font>();
        pr.readResetHasChanged<Text>();

        if (pr.get<Font>() && !(pr.get<Text>().empty()))
        {
            auto font(pr.get<Font>());
            auto texture(pr.get<Font>()->getTexture());

            // Create one quad for each character
            using counter_t = decltype(sceneNodes().size());

            counter_t counter{0U};
            counter_t const old_counter{sceneNodes().size()};
            auto const& text_color{pr.get<TextColor>()};
            auto const text_render_data{
                font_utils.getTextRenderData(pr.get<Text>())};
            vector2df current_text_position{};
            size_type indexChar{0U};

            auto const& current_text{pr.get<Text>()};
            types::sptr<SceneNodeLetter> letterNode;

            for (auto curChar : current_text)
            {
                // In case we already have a node containing the letter,
                // reuse it. If not, create a new one.
                if (counter < old_counter)
                {
                    letterNode = std::dynamic_pointer_cast<SceneNodeLetter>(
                        sceneNodes()[counter]);
                }
                else
                {
                    letterNode = createSceneNode<SceneNodeLetter>(
                        "text_" + str::to_str(counter));
                    letterNode->renderizableBuilder()
                        .name("text_" + str::to_str(counter))
                        .figType(render::FigType_t::Sprite)
                        .create();
                }

                prop<Scale>() = vector2df{1.0F / 200.0F, 1.0F / 150.0F};
//                prop<Scale>() = vector2df{1.0F / 200.0F, 1.0F / 150.0F};

                if (curChar == 'i')
                {
                    int c = 0;
                    (void)c;
                }

                {
                    auto character_render_data{
                        text_render_data.character_render_data[indexChar]};

                    auto prev_character_render_data{
                        indexChar > 0U
                            ? text_render_data
                                  .character_render_data[indexChar - 1U]
                            : res::CharacterRenderData{}};

                    current_text_position.x +=
                        character_render_data.characterBounds.left;

                    letterNode->prop<Position>() = current_text_position;
                    letterNode->prop<Scale>()    = {
                        character_render_data.characterBounds.width,
                        character_render_data.characterBounds.height};

                    current_text_position.x +=
                        character_render_data.characterAdvance;

                    letterNode->node()->prop<render::ColorProperty>().set(
                        text_color);

                    ++counter;
                    ++indexChar;

                    letterNode->setCharacterTextureData(
                        texture, font->getTextureBounds(curChar));
                }
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
            //            updateAlignmentX(
            //                getTransformation(inner_transformation_).prop<Position>(),
            //                prop<AlignmentX>().get(), textSize.width,
            //                pr.get<AlignmentSize>());
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

}  // namespace haf::scene::nodes
