#ifndef ZOPER_TEXTQUAD_HPP__
#define ZOPER_TEXTQUAD_HPP__

#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodes/nodetext.hpp>

namespace zoper
{
	class TextQuad
	{
	public:
		TextQuad(lib::draw::SceneNode *parent, lib::str name, lib::sptr<lib::draw::TTFont> font, lib::u32 characterSize, const lib::draw::Color &color, const lib::Rectf32 &box);
		virtual ~TextQuad() = default;

		lib::Property<lib::sptr<lib::draw::SceneNode>> sceneNode;
		lib::sptr<lib::draw::nodes::NodeText> text(lib::u32 index) const noexcept { return index < 4 ? m_texts[index] : nullptr; }

	private:
		lib::Rectf32 m_box;
		lib::sptr<lib::draw::nodes::NodeText> m_texts[4];
	};
}

#endif
