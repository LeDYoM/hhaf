#include "player.hpp"
#include "textquad.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::draw;

	TextQuad::TextQuad(SceneNode * parent, str_const name, lib::sptr<lib::draw::Font> font, u32 characterSize, const Color &color, const Rectf32 & box)
		: m_box{ box }
	{
		using namespace nodes;
		m_sceneNode = parent->createSceneNode<SceneNode>(name);
		u32 count{};
		for (auto &nodes : m_texts) {
			nodes = m_sceneNode->createRenderizable<nodes::NodeAlignedText>(name + "node_"+std::to_string(count++), "", font, characterSize, color, box, NodeAlignedText::AlignmentX::Left, NodeAlignedText::AlignmentY::Top);
		}
		
		// Second text is right aligned
		m_texts[1]->alignmentX = NodeAlignedText::AlignmentX::Right;

		// Third text is bottom aligned
		m_texts[2]->alignmentY = NodeAlignedText::AlignmentY::Bottom;

		// Fourth text is right and bottom aligned
		m_texts[3]->alignmentX = NodeAlignedText::AlignmentX::Right;
		m_texts[3]->alignmentY = NodeAlignedText::AlignmentY::Bottom;
	}
}
