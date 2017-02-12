#ifndef ZOPER_TEXTQUAD_HPP__
#define ZOPER_TEXTQUAD_HPP__

#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodes/nodetext.hpp>

namespace zoper
{
	class TextQuad
	{
	public:
		TextQuad(lib::draw::SceneNode *parent, lib::str_const name, const lib::Rectf32 &box);
		virtual ~TextQuad() = default;
	private:
		lib::sptr<lib::draw::SceneNode> m_sceneNode;
		lib::Rectf32 m_box;
		std::array<lib::sptr<lib::draw::nodes::NodeText>, 4> m_texts;
	};
}

#endif
