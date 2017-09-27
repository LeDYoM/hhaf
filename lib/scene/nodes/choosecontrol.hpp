#pragma once

#ifndef LIB_SCENE_CHOOSECONTROL_HPP__
#define LIB_SCENE_CHOOSECONTROL_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/discretetext.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include "optionmodel.hpp"

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			class LabelText;
			class ChooseControl : public scene::SceneNode
			{
			public:
				ChooseControl(lib::scene::SceneNode *parent, str name);
				virtual ~ChooseControl();

				void create() override;

				Property<Rectf32> box;
				using CompleteOptionModel = vector<OptionModel>;
				Property<CompleteOptionModel> optionModel;
				const OptionModelIndex currentSelection() const noexcept;

				void goDown();
				void goUp();
				void goLeft();
				void goRight();

				Property<u32> selectedItem;

			private:
				const sptr<LabelText> currentLine() const;
				const sptr<LabelText> previouscurrentLine() const;
				void modelChanged();
				u32 previouslySelectedItem;

				vector_shared_pointers<LabelText> lines;
			};
		}
	}
}

#endif
