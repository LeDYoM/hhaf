#include "menumanager.hpp"
#include <lib/core/log.hpp>
#include "imenucontrol.hpp"

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
			m_steps.clear();
		}

		void MenuManager::addMenuSteps(std::vector<sptr<IMenuControl>> &steps)
		{
			for (auto menuStep : steps)
			{
				addMenuStep(menuStep);
			}
		}

		void MenuManager::addMenuStep(sptr<IMenuControl> step)
		{
			addRenderGroup(step);
			m_steps.push_back(step);
			step->onCreate();
		}

		void MenuManager::start(sptr<IMenuControl> firstStep)
		{
			__ASSERT(firstStep, "Cannot start in nullptr step");
			changeStep(firstStep);
		}

		void MenuManager::start(const std::string &firstStep)
		{
			changeStep(firstStep);
		}

		void MenuManager::changeStep(const std::string &step)
		{
			for (const auto& nstep : m_steps)
			{
				if (nstep->name() == step)
				{
					changeStep(nstep);
				}
			}
		}

		void MenuManager::changeStep(sptr<IMenuControl> step)
		{
			setActiveStep(step);
		}

		void MenuManager::setActiveStep(sptr<IMenuControl> step)
		{
			m_activeMenuStep = step;

			for (auto _step : m_steps)
			{
				_step->setVisible(_step == step);
			}
		}
	}
}
