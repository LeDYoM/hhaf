#pragma once

#ifndef LIB_SCENE_CHOOSECONTROL_HPP__
#define LIB_SCENE_CHOOSECONTROL_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			class LabelText;
			class MenuPage : public scene::SceneNode
			{
			public:
				MenuPage(lib::scene::SceneNode *parent, str name);
				virtual ~MenuPage();

				void addLabel(const str &title, const str &option);

				void create() override;

				Property<Rectf32> box;

				void goDown();
				void goUp();
				void goLeft();
				void goRight();

				inline u32 selectedItem() const noexcept { return m_selectedItem; }

			private:
				inline const sptr<LabelText> currentLine() const { return lines[m_selectedItem]; }
				inline const sptr<LabelText> previouscurrentLine() const { return lines[m_previouslySelectedItem]; }
				u32 m_previouslySelectedItem;
				u32 m_selectedItem;

				vector_shared_pointers<LabelText> lines;
			};
		}
	}
}

#endif
