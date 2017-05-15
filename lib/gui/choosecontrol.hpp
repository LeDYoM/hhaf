#ifndef LIB_GUI_CHOOSECONTROL_HPP__
#define LIB_GUI_CHOOSECONTROL_HPP__

#include <lib/include/types.hpp>
#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodes/nodetext.hpp>
#include <lib/draw/nodes/discretetext.hpp>
#include <lib/draw/nodes/nodeshape.hpp>
#include "optionmodel.hpp"
#include <vector>
#include <functional>

namespace lib
{
	namespace core
	{
		class Resource;
	}
	namespace draw
	{
		class TTFont;
	}
	namespace gui
	{
		class ChooseControlLine;
		class ChooseControlGroup;
		class ChooseControl : public draw::SceneNode
		{
		public:
			ChooseControl(lib::draw::SceneNode *parent, str name);
			virtual ~ChooseControl();

			void create() override;

			Property<Rectf32> box;
			using CompleteOptionModel = std::vector<OptionModel>;
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
			draw::SceneNodeSPtr m_cursorNode;
			sptr<draw::nodes::NodeShape> m_cursor;
			std::function<void(const u32)> m_onSelected;
			friend class ChooseControlGroup;
		};
	}
}

#endif
