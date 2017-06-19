#include "player.hpp"
#include "textquad.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	TextQuad::TextQuad(SceneNode * parent, str name, lib::sptr<lib::scene::TTFont> font, u32 characterSize, const Color &color, const Rectf32 & box)
		: m_box{ box }
	{
		using namespace nodes;
		sceneNode = parent->createSceneNode<SceneNode>(name);
		u32 count{};
		for (auto &node : m_texts) {
			node = sceneNode()->createRenderizable<NodeText>(name + "node_" + str(count++));
			node->font = font;
			node->characterSize = characterSize;
			node->alignmentBox = box;
			node->alignmentX = NodeText::AlignmentX::Left;
			node->alignmentY = NodeText::AlignmentY::Top;
			node->color = color;
			node->configure();
		}

		// Second text is right aligned
		m_texts[1]->alignmentX = NodeText::AlignmentX::Right;

		// Third text is bottom aligned
		m_texts[2]->alignmentY = NodeText::AlignmentY::Bottom;

		// Fourth text is right and bottom aligned
		m_texts[3]->alignmentX = NodeText::AlignmentX::Right;
		m_texts[3]->alignmentY = NodeText::AlignmentY::Bottom;
	}
	TextQuad::~TextQuad()
	{
	}
}