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

			void addMenuSteps(std::vector<sptr<MenuStep>> &steps);
			void addMenuStep(sptr<MenuStep> step);

			void start(sptr<MenuStep> firstStep);
			void start(const std::string &firstStep);
			void changeStep(const std::string &step);
			void changeStep(sptr<MenuStep> step);
			virtual void onKeyPressed(sf::Event::KeyEvent kEvent);
			virtual void onKeyReleased(sf::Event::KeyEvent kEvent);

		private:
			void setActiveStep(sptr<MenuStep> step);

			std::vector<sptr<MenuStep>> _steps;
			sptr<MenuStep> _activeMenuStep{ nullptr };
		};
	}
}

#endif
