#ifndef LIB_GUI_CHOOSECONTROL_HPP__
#define LIB_GUI_CHOOSECONTROL_HPP__

#include <lib/include/types.hpp>
#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodes/nodetext.hpp>
#include <lib/draw/nodes/discretetext.hpp>
#include <lib/draw/nodes/nodeshape.hpp>
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
		class OptionDescriptor
		{
		public:
			explicit OptionDescriptor(str_const text, const string_vector &subOptionsLabels = string_vector())
				: _text{ text }, _subOptionsLabels(subOptionsLabels) {}

			std::string _text;
			string_vector _subOptionsLabels;
		};

		class ChooseControl : public draw::SceneNode
		{
		public:
			ChooseControl(lib::draw::SceneNode *parent, str_const &&name);
			virtual ~ChooseControl();

			void configure();
			ChooseControlGroup *chooseControlGroup() const;

			Property<std::function<void(const u32)>> onSelected;
			Property <std::vector<sptr<OptionDescriptor>>> options;
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

			std::vector<LabelData> m_labelData;
			draw::SceneNodeSPtr m_cursorNode;
			sptr<draw::nodes::NodeShape> m_cursor;
			std::function<void(const u32)> m_onSelected;

			friend class ChooseControlGroup;
		};
	}
}

#endif
