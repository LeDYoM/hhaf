#ifndef __LIB_CHOOSECONTROL_HPP__
#define __LIB_CHOOSECONTROL_HPP__

#include "../types.hpp"
#include "../scn/draw/renderizable.hpp"
#include "../scn/draw/rendergroup.hpp"
#include <vector>

namespace lib
{
	namespace menu
	{
		class MenuStep;
		class ChooseControl : public lib::scn::draw::RenderGroup
		{
		public:
			ChooseControl(const std::string &name, const std::vector<std::string> labels);
			virtual ~ChooseControl();

		private:
			std::vector<sptr<scn::draw::Renderizable>> _labels;
		};
	}
}

#endif
