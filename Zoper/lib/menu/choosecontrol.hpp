#ifndef __LIB_CHOOSECONTROL_HPP__
#define __LIB_CHOOSECONTROL_HPP__

#include "../types.hpp"
#include "../scn/draw/renderizable.hpp"
#include "imenucontrol.hpp"
#include "menudescriptors.hpp"
#include <vector>
#include <functional>

namespace lib
{
	namespace scn
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
			ChooseControl(const std::string &name, sptr<scn::Resource> font,
				const scn::draw::Alignment alignment,
				u32 chSize, float incY, std::function<void(const u32)> onSelected,
				sptr<CursorDescriptor> cursorDescriptor, 
				const std::vector<sptr<OptionDescriptor>> labels);
			virtual ~ChooseControl();

			virtual void onKeyPressed(sf::Event::KeyEvent kEvent);
			virtual void onKeyReleased(sf::Event::KeyEvent kEvent);

		private:
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
				sptr<scn::draw::Renderizable> subLabel{ nullptr };
				sptr<scn::draw::Renderizable> label{ nullptr };
				u32 selectedSublabel{ 0 };
				LabelData(const std::vector<std::string> textSubLevel_, sptr<scn::draw::Renderizable> subLabel_,
					sptr<scn::draw::Renderizable> label_, const u32 selectedSubLabel_)
					: textSubLabel(textSubLevel_), subLabel{ subLabel_ }, label{ label_ }, selectedSublabel{ selectedSubLabel_ } {}
			};
			std::vector<LabelData> _labelData;
			sptr<scn::draw::Renderizable> _cursor;
			std::function<void(const u32)> _onSelected;
		};
	}
}

#endif
