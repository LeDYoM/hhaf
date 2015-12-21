#ifndef __LIB_MENUMANAGER_HPP__
#define __LIB_MENUMANAGER_HPP__

#include <vector>
#include "../types.hpp"
#include "../scn/scene.hpp"

namespace lib
{
	namespace menu
	{
		class MenuStep;
		class MenuManager : public scn::Scene
		{
		public:
			MenuManager(const std::string &name);
			virtual ~MenuManager();

			void addMenuSteps(const std::vector<sptr<MenuStep>> &steps);
			void addMenuStep(sptr<MenuStep> step);
		private:
			std::vector<sptr<MenuStep>> _steps;
		};
	}
}

#endif
