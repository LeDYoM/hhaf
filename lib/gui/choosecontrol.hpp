#ifndef LIB_GUI_CHOOSECONTROL_HPP__
#define LIB_GUI_CHOOSECONTROL_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/discretetext.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include "optionmodel.hpp"

namespace lib
{
	namespace core
	{
		class Resource;
	}
	namespace scene
	{
		class TTFont;
	}
	namespace gui
	{
		class ChooseControlLine;
		class ChooseControlGroup;
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

			u32 selectedSubLabel(const u32 index) const;

		private:
			void goDown();
			void goUp();
			void goLeft();
			void goRight();
			const sptr<ChooseControlLine> currentLine() const;
			const sptr<ChooseControlLine> previouscurrentLine() const;
			void modelChanged();
			vector2df descriptorCursorSize;
			u32 previouslySelectedItem;
			Property<u32> selectedItem;

			vector_shared_pointers<ChooseControlLine> lines;
			scene::SceneNodeSPtr m_cursorNode;
			sptr<scene::nodes::NodeShape> m_cursor;
			function<void(const u32)> m_onSelected;
			friend class ChooseControlGroup;
		};
	}
}

#endif
