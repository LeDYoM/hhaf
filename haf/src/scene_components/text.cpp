#include <haf/include/scene_components/text.hpp>
#include <haf/include/scene_components/renderizable_group_component.hpp>
#include <haf/include/render/renderizables.hpp>

#include "resources/font_utils.hpp"

#include <haf/include/resources/ifont.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/scene/scenenode_cast.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace fmath;

namespace haf::scene
{

namespace
{
inline void updateAlignmentX(prop::PropertyState<vector2df>& position,
                             Text::AlignmentXModes const alignmentX,
                             f32 const textSizeX,
                             vector2df const& alignmentSize) noexcept
{
    f32 newPosX{0.f};

    switch (alignmentX)
    {
        default:
        case Text::AlignmentXModes::Left:
            break;
        case Text::AlignmentXModes::Center:
            newPosX = (alignmentSize.x / 2) - (textSizeX / 2);
            break;
        case Text::AlignmentXModes::Right:
            newPosX = (alignmentSize.x - textSizeX);
            break;
    }

    position = {newPosX, position().y};
}

inline void updateAlignmentY(prop::PropertyState<vector2df>& position,
                             Text::AlignmentYModes const alignmentY,
                             f32 const textSizeY,
                             vector2df const& alignmentSize) noexcept
{
    f32 newPosY{0.f};

    switch (alignmentY)
    {
        default:
        case Text::AlignmentYModes::Top:
            break;
        case Text::AlignmentYModes::Middle:
            newPosY = (alignmentSize.y / 2) - (textSizeY / 2);
            break;
        case Text::AlignmentYModes::Bottom:
            newPosY = alignmentSize.y - textSizeY;
            break;
    }

    position = {position().x, newPosY};
}

inline TextBaseSize updateTextRenderData(res::FontUtils const& font_utils,
                                         TextBaseSize const& text_base_size)
{
    if (!text_base_size.text().empty())
    {
        return {text_base_size.text(),
                font_utils.getTextRenderData(text_base_size.text()).text_size};
    }

    return text_base_size.value();
}

}  // namespace

void Text::onAttached()
{
    m_inner_scale_scene_node =
        attachedNode()->createSceneNode("inner_scale_scene_node");
    m_inner_position_scene_node =
        m_inner_scale_scene_node->createSceneNode("inner_position_scene_node");

    m_letters_scene_node = m_inner_position_scene_node;
}

void Text::update()
{
    if (ps_readResetHasAnyChanged(Font, Text, TextBaseSizeProperty))
    {
        m_letters_scene_node->clearSceneNodes();
        if (Font() != nullptr && !(Text().empty()))
        {
            auto font{Font().get()};
            // TODO: Select texture for character
            auto texture_str{font->getTexture(0)};
            if (!texture_str.empty())
            {
                auto texture{attachedNode()
                                 ->subSystem<res::IResourceRetriever>()
                                 ->getTexture(texture_str)};

                // Get the text to render
                auto const& current_text{Text()};

                // Get The text color for each character
                auto const text_color{TextColor()};

                // Initialize the index of the current character
                size_type indexChar{0U};

                // Prepare the text render data

                // Create the font utils to use
                res::FontUtils const font_utils{font};

                // Update the text base size property. If it contains a text, it
                // has preference, but prepare the size value of these text and
                // update the property accordinly.
                TextBaseSizeProperty =
                    updateTextRenderData(font_utils, TextBaseSizeProperty());

                // This was an internal change. Forget it happened.
                TextBaseSizeProperty.resetHasChanged();

                auto const text_render_data{
                    font_utils.getTextRenderData(current_text)};

                auto const text_base_size{TextBaseSizeProperty()};

                vector2df const text_render_size{
                    text_base_size.value().x == f32{}
                        ? text_render_data.text_size.x
                        : text_base_size.value().x,
                    text_base_size.value().y == f32{}
                        ? text_render_data.text_size.y
                        : text_base_size.value().y};

                m_inner_scale_scene_node->Scale =
                    vector2df{1.0F / text_render_size};

                m_inner_position_scene_node->Position =
                    -(text_render_size / 2.0F);

                // Initialize the node for each letter we are going to use
                sptr<SceneNode> letterNode;

                for (auto curChar : current_text)
                {
                    letterNode = m_letters_scene_node->createSceneNode(
                        "text_" + str::to_str(indexChar));
                    auto node{
                        letterNode->component<RenderizableGroupComponent>()};
                    node->renderizableBuilder()
                        .name("text_" + str::to_str(indexChar))
                        .figType(render::FigType_t::Sprite)
                        .create();

                    auto const& ch_data{
                        text_render_data.character_render_data[indexChar]};

                    letterNode->Position = ch_data.character_position;
                    letterNode->Scale    = ch_data.character_size;

                    node->first()->material().color = text_color;

                    node->first()->material().texture = texture;
                    node->first()->material().textureRect =
                        font->getTextureBounds(curChar);

                    ++indexChar;
                }

                // Avoid update color
                TextColor.resetHasChanged();
            }
        }
    }

    if (TextColor.readResetHasChanged())
    {
        Color const& text_color{TextColor()};

        m_letters_scene_node->for_each_sceneNode(
            [&text_color](sptr<SceneNode> const& sNode) {
                auto node{sNode->componentOfType<RenderizableGroupComponent>()};
                node->first()->material().color = text_color;
            });
    }
}

}  // namespace haf::scene
