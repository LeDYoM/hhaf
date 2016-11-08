#include "menumanager.hpp"
#include <lib/core/log.hpp>
#include "choosecontrol.hpp"

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

		void MenuManager::addMenuSteps(const std::vector<sptr<ChooseControl>> &steps)
		{
			for (auto menuStep : steps)
			{
				addMenuStep(menuStep);
			}
		}

		void MenuManager::addMenuStep(sptr<ChooseControl> step)
		{
			addRenderGroup(step);
			m_steps.push_back(step);
		}

		void MenuManager::start(sptr<ChooseControl> &firstStep)
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
			for (auto& nstep : m_steps) {
				if (nstep->name() == step) {
					changeStep(nstep);
					break;
				}
			}
		}

		void MenuManager::changeStep(sptr<ChooseControl> &step)
		{
			setActiveStep(step);
		}

		void MenuManager::setActiveStep(sptr<ChooseControl> &step)
		{
			m_activeMenuStep = step;

			for (const auto &_step : m_steps) {
				_step->setVisible(_step == step);
			}
		}
	}
}
