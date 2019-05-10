#include "alignedtextcomponent.hpp"

#include <lib/scene/nodes/scenenodetext.hpp>

#include <lib/resources/font.hpp>

namespace lib::scene
{

    void AlignedTextComponent::update()
    {
        const bool as_rr_hasChanged{ alignmentSize.readResetHasChanged() };

        const auto nodeText(
                    attachedNodeAs<nodes::SceneNodeText>());
        if (as_rr_hasChanged || alignmentX.readResetHasChanged()) {
            updateAlignmentX(nodeText->font()->textSize(
                                 nodeText->text()()).x);
        }

        if (as_rr_hasChanged || alignmentY.readResetHasChanged())
        {
            updateAlignmentY(nodeText->font()->textSize(
                                 nodeText->text()()).y);
        }
    }

    void AlignedTextComponent::updateAlignmentX(const f32 textSizeX)
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

        attachedNode()->position.set(vector2df{newPosX,
                                               attachedNode()->position().y});

    }

    void AlignedTextComponent::updateAlignmentY(const f32 textSizeY)
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

        attachedNode()->position.set(
                    vector2df{attachedNode()->position().x, newPosY});
    }
}
