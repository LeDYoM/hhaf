#include "textgroup.hpp"

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			TextGroup::TextGroup(SceneNode * parent, str name, sptr<TTFont> font, const u32 characterSize, const Color &color, const Rectf32 & box)
				: SceneNode{ parent, std::move(name) }, m_box { box }
			{
				u32 count{};
				for (auto &node : m_texts) {
					node = createRenderizable<NodeText>(name + "node_" + str(count++));
					node->font = font;
					node->characterSize = characterSize;
					node->alignmentBox = box;
					node->alignmentX = AlignmentX::Left;
					node->alignmentY = AlignmentY::Top;
					node->color = color;
				}

				// Second text is right aligned
				m_texts[1]->alignmentX = AlignmentX::Right;

				// Third text is bottom aligned
				m_texts[2]->alignmentY = AlignmentY::Bottom;

				// Fourth text is right and bottom aligned
				m_texts[3]->alignmentX = AlignmentX::Right;
				m_texts[3]->alignmentY = AlignmentY::Bottom;
			}

			TextGroup::~TextGroup() = default;
		}
	}
}