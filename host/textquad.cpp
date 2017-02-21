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
		sceneNode = parent->createSceneNode<SceneNode>(name);
		u32 count{};
		for (auto &nodes : m_texts) {
			nodes = sceneNode()->createRenderizable<nodes::NodeText>(name + "node_"+std::to_string(count++), "", font, characterSize, color, box, NodeText::AlignmentX::Left, NodeText::AlignmentY::Top);
		}
		
		// Second text is right aligned
		m_texts[1]->alignmentX = NodeText::AlignmentX::Right;

		// Third text is bottom aligned
		m_texts[2]->alignmentY = NodeText::AlignmentY::Bottom;

		// Fourth text is right and bottom aligned
		m_texts[3]->alignmentX = NodeText::AlignmentX::Right;
		m_texts[3]->alignmentY = NodeText::AlignmentY::Bottom;
	}
}
