#include "textgroup.hpp"

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			TextGroup::TextGroup(SceneNode *parent, str name, Color color, nodes::NodeTextPropertyGroup  initValues)
				: SceneNode{ parent, std::move(name) }, NodeTextPropertyGroup{ std::move(initValues) }
			{
				u32 count{};
				for (auto &node : m_texts) {
					node = createRenderizable<NodeText>(name + "node_" + str(count++));
					node->font = font;
					node->characterSize = characterSize;
//					node->alignmentBox = box;
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