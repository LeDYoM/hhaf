#ifndef __LIB_MENUMANAGER_HPP__
#define __LIB_MENUMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/draw/scene.hpp>

namespace lib
{
	namespace menu
	{
		class IMenuControl;
		class MenuManager : public lib::scn::Scene
		{
		public:
			MenuManager(const std::string &name);
			virtual ~MenuManager();

			void addMenuSteps(std::vector<sptr<IMenuControl>> &steps);
			void addMenuStep(sptr<IMenuControl> step);

			void start(sptr<IMenuControl> firstStep);
			void start(const std::string &firstStep);
			void changeStep(const std::string &step);
			void changeStep(sptr<IMenuControl> step);

		private:
			void setActiveStep(sptr<IMenuControl> step);

			std::vector<sptr<IMenuControl>> m_steps;
			sptr<IMenuControl> m_activeMenuStep{ nullptr };
		};
	}
}

#endif
