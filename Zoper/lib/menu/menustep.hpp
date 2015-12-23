#ifndef __LIB_MENUSTEP_HPP__
#define __LIB_MENUSTEP_HPP__

#include "../scn/draw/rendergroup.hpp"
#include <memory>

namespace lib
{
	namespace menu
	{
		class MenuManager;
		class MenuStep : public scn::draw::RenderGroup
		{
		public:
			MenuStep(const std::string &name);
			virtual ~MenuStep();

			virtual void onCreate() = 0;
			MenuManager *menuManager();

		};
	}
}

#endif
