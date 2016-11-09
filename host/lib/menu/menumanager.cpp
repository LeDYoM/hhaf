#include "menumanager.hpp"
#include "choosecontrol.hpp"

#include <lib/core/log.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>

namespace lib
{
	namespace menu
	{
		MenuManager::MenuManager(const std::string &name, Theme theme)
			: scn::Scene{ name }, m_theme( theme )
		{
			m_theme.font = host().resourceManager().getResource("game_menu.mainFont");
			m_theme.textColor = sf::Color::Blue;
			m_theme.selectedTextColor = sf::Color::Red;
			m_theme.alignment = scn::draw::Alignment::Center;
			m_theme.chSize = 70;
			m_theme.incY = 1;
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

		const Theme & MenuManager::currentTheme() const noexcept
		{
			return m_theme;
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
