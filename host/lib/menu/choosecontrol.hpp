#ifndef LIB_GUI_CHOOSECONTROL_HPP__
#define LIB_GUI_CHOOSECONTROL_HPP__

#include <lib/include/types.hpp>
#include <lib/draw/rendergroup.hpp>
#include <vector>
#include <functional>

namespace lib
{
	namespace core
	{
		class Resource;
	}
	namespace menu
	{
		class OptionDescriptor
		{
		public:
			explicit OptionDescriptor(const std::string &text, bool createSubString = false, u32 startValueIndex = 0,
				const std::vector<std::string> &subOptionsLabels = std::vector<std::string>())
				: _text(text), _createSubString{ createSubString }, _startValueIndex{ startValueIndex },
				_subOptionsLabels(subOptionsLabels) {}

			std::string _text;
			bool _createSubString;
			u32 _startValueIndex;
			std::vector<std::string> _subOptionsLabels;
		};
		class MenuManager;
		class ChooseControl : public draw::RenderGroup
		{
		public:
			ChooseControl(const std::string &name, MenuManager *parent, std::function<void(const u32)> onSelected,
				const std::vector<sptr<OptionDescriptor>> labels);
			virtual ~ChooseControl();

			MenuManager *menuManager() const;

			u32 getSelectedSubLabel(u32 index) const;
			void setSelectedSubLabel(u32 index, u32 subIndex);

			void onAddedToScene() override {}

		private:
			void updateSubLabelText(const u32 index);
			void cursorSelectItem(u32 nodeIndex);
			void goDown();
			void goUp();
			void goLeft();
			void goRight();

			vector2df descriptorCursorSize;
			u32 _cursorItemSelected{ 0 };

			struct LabelData
			{
				std::vector<std::string> textSubLabel;
				sptr<draw::NodeText> subLabel{ nullptr };
				sptr<draw::NodeText> label{ nullptr };
				u32 selectedSublabel{ 0 };
				LabelData(const std::vector<std::string> textSubLevel_, sptr<draw::NodeText> subLabel_,
					sptr<draw::NodeText> label_, const u32 selectedSubLabel_)
					: textSubLabel(textSubLevel_), subLabel{ subLabel_ }, label{ label_ }, selectedSublabel{ selectedSubLabel_ } {}
			};

			std::vector<LabelData> _labelData;
			sptr<draw::NodeShape> _cursor;
			std::function<void(const u32)> m_onSelected;

			friend class MenuManager;
		};
	}
}

#endif
