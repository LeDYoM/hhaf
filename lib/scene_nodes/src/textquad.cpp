#include "textquad.hpp"

namespace lib::scene::nodes
{
    TextQuad::TextQuad(SceneNode * parent, str name, sptr<IFont> font, const Color &color,
                       const vector2df & size)
        : BaseClass{ parent, std::move(name) }
    {
        setTableSize({2,2});
        for (size_type count{0}; count < 4U; ++count)
        {
            auto node = createNodeAt({count%2, count/2}, name + "node_" + make_str(count));
            node->font = font;
            node->textColor.set(color);
        }

        // Second text is right aligned
        {
            auto align(nodeAt({1,0}));
            align->alignmentSize.set(size);
            align->alignmentX.set(SceneNodeText::AlignmentX::Right);
            align->alignmentY.set(SceneNodeText::AlignmentY::Top);
        }

        // Third text is bottom aligned
        {
            auto align(nodeAt({0,1}));
            align->alignmentSize.set(size);
            align->alignmentX.set(SceneNodeText::AlignmentX::Left);
            align->alignmentY.set(SceneNodeText::AlignmentY::Bottom);
        }

        // Fourth text is right and bottom aligned
        {
            auto align(nodeAt({1,1}));
            align->alignmentSize.set(size);
            align->alignmentX.set(SceneNodeText::AlignmentX::Right);
            align->alignmentY.set(SceneNodeText::AlignmentY::Bottom);
        }
    }

    TextQuad::~TextQuad() = default;
}
