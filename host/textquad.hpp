#ifndef ZOPER_TEXTQUAD_HPP__
#define ZOPER_TEXTQUAD_HPP__

#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodes/nodealignedtext.hpp>

namespace zoper
{
	class TextQuad
	{
	public:
		TextQuad(lib::draw::SceneNode *parent, lib::str_const name, lib::sptr<lib::draw::Font> font, lib::u32 characterSize, const lib::draw::Color &color, const lib::Rectf32 &box);
		virtual ~TextQuad() = default;
	private:
		lib::sptr<lib::draw::SceneNode> m_sceneNode;
		lib::Rectf32 m_box;
		std::array<lib::sptr<lib::draw::nodes::NodeAlignedText>, 4> m_texts;
	};
}

#endif
