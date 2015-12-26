#ifndef __LIB_CHOOSECONTROL_HPP__
#define __LIB_CHOOSECONTROL_HPP__

#include "../types.hpp"
#include "../scn/draw/renderizable.hpp"
#include "imenucontrol.hpp"
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
			ChooseControl(const std::string &name, sptr<scn::Resource> font, sptr<scn::draw::Renderizable> cursor, const std::vector<sptr<OptionDescriptor>> labels);
			virtual ~ChooseControl();

		private:
			std::vector<sptr<scn::draw::Renderizable>> _labels;
			sptr<scn::draw::Renderizable> _cursor;
		};
	}
}

#endif
