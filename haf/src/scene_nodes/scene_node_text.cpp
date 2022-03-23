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

void SceneNodeText::onCreated()
{
    inner_transformation_ = addTransformation();
}

void SceneNodeText::update()
{
    res::FontUtils const font_utils{prop<Font>()().get()};

    if (ps_readResetHasAnyChanged(prop<Font>(), prop<Text>()))
    {
        if (prop<Font>()() != nullptr && !(prop<Text>()().empty()))
        {
            auto font{prop<Font>()()};
            auto texture{prop<Font>()()->getTexture()};

            // Initialize counter of characters
            types::size_type counter{0U};

            // Get the counter of letters in the previous text set
            types::size_type const old_counter{sceneNodes().size()};

            // Get the text to render
            auto const& current_text{prop<Text>()()};

            // Get The text color for each character
            auto const text_color{prop<TextColor>()()};

            // Prepare the text render data
            auto const text_render_data{
                font_utils.getTextRenderData(current_text)};

            // Initialize the index of the current character
            size_type indexChar{0U};

            // Initialize the node for each letter we are going to use
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

                getTransformation(inner_transformation_).prop<Scale>() =
                    vector2df{1.0F / text_render_data.text_size};

                auto const& character_render_data{
                    text_render_data.character_render_data[indexChar]};

                vector2df new_position{
                    character_render_data.character_position.x -
                        (text_render_data.text_size.x / 2.0F),
                    character_render_data.character_position.y -
                        (text_render_data.text_size.y / 2.0F)};

                letterNode->prop<Position>() = new_position;
                letterNode->prop<Scale>() =
                    character_render_data.character_size;

                letterNode->node()->prop<render::ColorProperty>().set(
                    text_color);

                letterNode->setCharacterTextureData(
                    texture, font->getTextureBounds(curChar));

                ++counter;
                ++indexChar;
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

            // Force update color
            prop<TextColor>().resetHasChanged();
        }
        else
        {
            clearSceneNodes();
        }
    }

    if (prop<TextColor>().readResetHasChanged())
    {
        Color const& text_color{prop<TextColor>()()};

        for_each_sceneNode_as<RenderizableSceneNode>(
            [&text_color](types::sptr<RenderizableSceneNode> const& sNode) {
                sNode->node()->prop<render::ColorProperty>() = text_color;
            });
    }
}

}  // namespace haf::scene::nodes
