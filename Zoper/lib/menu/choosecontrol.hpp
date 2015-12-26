#ifndef __LIB_CHOOSECONTROL_HPP__
#define __LIB_CHOOSECONTROL_HPP__

#include "../types.hpp"
#include "../scn/draw/renderizable.hpp"
#include "imenucontrol.hpp"
#include "menudescriptors.hpp"
#include <vector>

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
				u32 chSize,
				float incY,
				sptr<CursorDescriptor> cursorDescriptor, 
				const std::vector<sptr<OptionDescriptor>> labels);
			virtual ~ChooseControl();

		private:
			void cursorSelectItem(u32 nodeIndex);

			vector2df descriptorCursorSize;
			u32 _cursorItemSelected{ 0 };
			std::vector<sptr<scn::draw::Renderizable>> _labels;
			sptr<scn::draw::Renderizable> _cursor;
		};
	}
}

#endif
