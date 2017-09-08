#ifndef ZOPER_TEXTQUAD_HPP__
#define ZOPER_TEXTQUAD_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace zoper
{
	class TextQuad
	{
	public:
		TextQuad(lib::scene::SceneNode *parent, lib::str name, lib::sptr<lib::scene::TTFont> font, lib::u32 characterSize, const lib::scene::Color &color, const lib::Rectf32 &box);
		virtual ~TextQuad();
			

		lib::Property<lib::sptr<lib::scene::SceneNode>> sceneNode;
		lib::sptr<lib::scene::nodes::NodeText> text(lib::u32 index) const noexcept { return index < 4 ? m_texts[index] : nullptr; }

	private:
		lib::Rectf32 m_box;
		lib::sptr<lib::scene::nodes::NodeText> m_texts[4];
	};
}

#endif
