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
		class Font;
	}
	namespace gui
	{
		class ChooseControlLine;
		class ChooseControlGroup;
		class ChooseControl : public draw::SceneNode
		{
		public:
			ChooseControl(lib::draw::SceneNode *parent, str_const &&name);
			virtual ~ChooseControl();

			void configure();
			ChooseControlGroup *chooseControlGroup() const;

			Property <std::vector<OptionModel>> options;
			std::vector<u32> selection() const;

			u32 selectedSubLabel(const u32 index) const;

		private:
			void cursorSelectItem(const u32 nodeIndex);
			void goDown();
			void goUp();
			void goLeft();
			void goRight();

			vector2df descriptorCursorSize;
			u32 _cursorItemSelected{ 0 };

			struct LabelData
			{
				sptr<ChooseControlLine> node;
				LabelData(const sptr<ChooseControlLine> &nodep)
					: node{ nodep } {}
			};

			std::vector<sptr<ChooseControlLine>> lines;
			draw::SceneNodeSPtr m_cursorNode;
			sptr<draw::nodes::NodeShape> m_cursor;
			std::function<void(const u32)> m_onSelected;

			friend class ChooseControlGroup;
		};
	}
}

#endif
