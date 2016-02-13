#ifndef __LIB_CHOOSECONTROL_HPP__
#define __LIB_CHOOSECONTROL_HPP__

#include <lib/include/types.hpp>
#include <lib/draw/renderizable.hpp>
#include "imenucontrol.hpp"
#include "menudescriptors.hpp"
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
		class OptionDescriptor;
		class MenuStep;
		class ChooseControl : public IMenuControl
		{
		public:
			ChooseControl(const std::string &name, sptr<core::Resource> font,
				const sf::Color &textColor, const sf::Color &selectedTextColor,
				const scn::draw::Alignment alignment,
				u32 chSize, float incY, std::function<void(const u32,ChooseControl &self)> onSelected,
				sptr<CursorDescriptor> cursorDescriptor, 
				const std::vector<sptr<OptionDescriptor>> labels);
			virtual ~ChooseControl();

			u32 getSelectedSubLabel(u32 index) const;
			void setSelectedSubLabel(u32 index, u32 subIndex);
		private:
			virtual void onKeyPressed(sf::Event::KeyEvent kEvent);
			virtual void onKeyReleased(sf::Event::KeyEvent kEvent);

			void updateSubLabelText(const u32 index);
			void cursorSelectItem(u32 nodeIndex);
			void goDown();
			void goUp();
			void goLeft();
			void goRight();

			vector2df descriptorCursorSize;
			u32 _cursorItemSelected{ 0 };
			sf::Color _textColor;
			sf::Color _selectedTextColor;

			struct LabelData
			{
				std::vector<std::string> textSubLabel;
				sptr<scn::draw::NodeText> subLabel{ nullptr };
				sptr<scn::draw::NodeText> label{ nullptr };
				u32 selectedSublabel{ 0 };
				LabelData(const std::vector<std::string> textSubLevel_, sptr<scn::draw::NodeText> subLabel_,
					sptr<scn::draw::NodeText> label_, const u32 selectedSubLabel_)
					: textSubLabel(textSubLevel_), subLabel{ subLabel_ }, label{ label_ }, selectedSublabel{ selectedSubLabel_ } {}
			};
			std::vector<LabelData> _labelData;
			sptr<scn::draw::NodeShape> _cursor;
			std::function<void(const u32, ChooseControl &self)> _onSelected;
		};
	}
}

#endif
