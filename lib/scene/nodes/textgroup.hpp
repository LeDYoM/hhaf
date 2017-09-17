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

				void addText(str nText);
				inline sptr<NodeText> operator[](u32 index) const noexcept { return m_texts[index]; }
				inline u32 numTexts() const noexcept { return m_texts.size(); }

				Property<sptr<scene::TTFont>> font;
				Property<Color> color;
				Property<u32> characterSize;

			protected:
				void setGroupProperties(const sptr<NodeText> &nText);
			private:
				Rectf32 m_box;
				vector<sptr<NodeText>> m_texts;
			};
		}
	}
}

#endif
