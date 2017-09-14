#pragma once

#ifndef LIB_SCENE_TEXTGROUP_HPP__
#define LIB_SCENE_TEXTGROUP_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			class TextGroup : public SceneNode
			{
			public:
				TextGroup(SceneNode *parent, str name);
				virtual ~TextGroup();

				void create() override;
				inline sptr<NodeText> text(const u32 index) const noexcept { return m_texts[index]; }

				void setFont(sptr<scene::TTFont> f) noexcept;
				void setColor(const Color &c) noexcept;
				void setCharacterSize(const u32 cs) noexcept;
			private:
				Rectf32 m_box;
				vector<sptr<NodeText>> m_texts;
			};
		}
	}
}

#endif
