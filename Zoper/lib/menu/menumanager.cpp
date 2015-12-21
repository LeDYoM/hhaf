#include "menumanager.hpp"
#include "../log.hpp"

namespace lib
{
	namespace menu
	{
		MenuManager::MenuManager(const std::string &name)
			: scn::Scene{ name }
		{
		}


		MenuManager::~MenuManager()
		{
			_steps.clear();
		}

		void MenuManager::addMenuSteps(const std::vector<sptr<MenuStep>> &steps)
		{
			for (auto menuStep : steps)
			{
				addMenuStep(menuStep);
			}
		}

		void MenuManager::addMenuStep(sptr<MenuStep> step)
		{

		}
	}
}
