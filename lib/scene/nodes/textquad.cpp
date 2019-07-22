#include "textquad.hpp"

#include <lib/scene/components/alignedtextcomponent.hpp>

namespace lib::scene::nodes
{
    TextQuad::TextQuad(SceneNode * parent, str name, sptr<IFont> font, const Color &color,
                       const vector2df & size)
        : BaseClass{ parent, std::move(name) }, m_size { size }
    {
        setTableSize({2,2});
        for (size_type count{0}; count < 4; ++count)
        {
            auto node = createNodeAt({count%2, count/2}, name + "node_" + make_str(count));
            node->font = font;
            node->textColor.set(FillColor_t(color));
        }

        // Second text is right aligned
        {
            auto align(nodeAt({1,0})->addComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(size);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Right);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Top);
        }

        // Third text is bottom aligned
        {
            auto align(nodeAt({0,1})->addComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(size);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Left);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Bottom);
        }

        // Fourth text is right and bottom aligned
        {
            auto align(nodeAt({1,1})->addComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(size);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Right);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Bottom);
        }
    }

    TextQuad::~TextQuad() = default;
}
