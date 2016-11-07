#ifndef __LIB_MENUMANAGER_HPP__
#define __LIB_MENUMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/draw/scene.hpp>

namespace lib
{
	namespace menu
	{
		class ChooseControl;
		class MenuManager : public lib::scn::Scene
		{
		public:
			MenuManager(const std::string &name);
			virtual ~MenuManager();

			void addMenuSteps(std::vector<sptr<ChooseControl>> &steps);
			void addMenuStep(sptr<ChooseControl> step);

			void start(sptr<ChooseControl> firstStep);
			void start(std::string firstStep);
			void changeStep(std::string step);
			void changeStep(sptr<ChooseControl> step);

		private:
			void setActiveStep(sptr<ChooseControl> step);

			std::vector<sptr<ChooseControl>> m_steps;
			sptr<ChooseControl> m_activeMenuStep{ nullptr };
		};
	}
}

#endif
