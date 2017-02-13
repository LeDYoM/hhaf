#include "player.hpp"
#include "textquad.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::draw;

	TextQuad::TextQuad(SceneNode * parent, str_const name, const Rectf32 & box)
		: m_box{ box }
	{
		m_sceneNode = parent->createSceneNode<SceneNode>(name);
//		m_texts[0] = m_sceneNode->createRenderizable<nodes::NodeText>(name+"node_0","",)
		
	}
}
