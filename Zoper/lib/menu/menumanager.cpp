#include "menumanager.hpp"
#include "menustep.hpp"
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
			addRenderGroup(step);
		}

		void MenuManager::start(sptr<MenuStep> firstStep)
		{
			__ASSERT(firstStep, "Cannot start in nullptr step");
		}

		void MenuManager::changeStep(const std::string &step)
		{
			for (const auto nstep : _steps)
			{
				if (nstep->name() == step)
				{
					setActiveStep(nstep);
				}
			}
		}

		void MenuManager::setActiveStep(sptr<MenuStep> step)
		{
			_activeMenuStep = step;

			for (auto _step : _steps)
			{
				_step->setVisible(_step == step);
			}
		}
	}
}
