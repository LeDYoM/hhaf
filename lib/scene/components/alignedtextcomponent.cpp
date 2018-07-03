#include "alignedtextcomponent.hpp"

#include <lib/scene/nodes/scenenodetext.hpp>
#include <lib/scene/ttfont.hpp>

namespace lib::scene
{

    void AlignedTextComponent::update()
    {
        const bool ab_rr_hasChanged{ alignmentBox.readResetHasChanged() };

        const auto nodeText(
                    attachedNodeAs<nodes::SceneNodeText>());
        if (ab_rr_hasChanged || alignmentX.readResetHasChanged()) {
            updateAlignmentX(nodeText->font()->textBox(
                                 nodeText->text()(),
                                 nodeText->characterSize()));
        }

        if (ab_rr_hasChanged || alignmentY.readResetHasChanged())
        {
            updateAlignmentY(nodeText->font()->textBox(
                                 nodeText->text()(),
                                 nodeText->characterSize()));
        }
    }

    void AlignedTextComponent::updateAlignmentX(const Rectf32 textSize)
    {
        switch (alignmentX())
        {
        default:
        case AlignmentX::Left:
            attachedNode()->position.set(vector2df{0,
                                               attachedNode()->position().y});
            break;
        case AlignmentX::Center:
        {
            const auto &abox( alignmentBox() );
            attachedNode()->position.set(
                        {abox.left + (abox.width / 2.f) - (textSize.width / 2),
                        attachedNode()->position().y});
        }
        break;
        case AlignmentX::Right:
            attachedNode()->position.set(
                        {alignmentBox().right() - textSize.right(),
                         attachedNode()->position().y});
            break;
        }
    }

    void AlignedTextComponent::updateAlignmentY(const Rectf32 textSize)
    {
        switch (alignmentY())
        {
        default:
        case AlignmentY::Top:
            attachedNode()->position.set(
                        vector2df{attachedNode()->position().x, 0});
            break;
        case AlignmentY::Middle:
        {
            const auto &abox{ alignmentBox() };
            attachedNode()->position.set(
                        vector2df{attachedNode()->position().x,
                        abox.top + (abox.height / 2.f) - (textSize.height / 2)
                        });
        }
        break;
        case AlignmentY::Bottom:
            attachedNode()->position.set(
                        vector2df{attachedNode()->position().x,
                        alignmentBox().bottom() - textSize.bottom()});
            break;
        }
    }
}
