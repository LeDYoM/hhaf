#ifndef __LIB_MENUSTEP_HPP__
#define __LIB_MENUSTEP_HPP__

#include "../scn/draw/rendergroup.hpp"

namespace lib
{
	namespace menu
	{
		class MenuStep : public scn::draw::RenderGroup
		{
		public:
			MenuStep(const std::string &name);
			virtual ~MenuStep();
		};
	}
}

#endif
