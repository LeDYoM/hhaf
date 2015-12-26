#ifndef __LIB_MENUSTEP_HPP__
#define __LIB_MENUSTEP_HPP__

#include "../scn/draw/rendergroup.hpp"
#include "../menu/imenucontrol.hpp"
#include "../types.hpp"

#include <vector>
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

			void addMenuControl(sptr<IMenuControl> nControl);
		private:
			std::vector<sptr<IMenuControl>> _controls;
		};
	}
}

#endif
