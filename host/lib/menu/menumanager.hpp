#ifndef __LIB_MENUMANAGER_HPP__
#define __LIB_MENUMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/draw/scene.hpp>
#include "menustep.hpp"

namespace lib
{
	namespace menu
	{
		class MenuManager : public lib::scn::Scene
		{
		public:
			MenuManager(const std::string &name);
			virtual ~MenuManager();

			void addMenuSteps(std::vector<sptr<MenuControl>> &steps);
			void addMenuStep(sptr<MenuControl> step);

			void start(sptr<MenuControl> firstStep);
			void start(const std::string &firstStep);
			void changeStep(const std::string &step);
			void changeStep(sptr<MenuControl> step);

		private:
			void setActiveStep(sptr<MenuControl> step);

			std::vector<sptr<MenuControl>> _steps;
			sptr<MenuControl> _activeMenuStep{ nullptr };
		};
	}
}

#endif
