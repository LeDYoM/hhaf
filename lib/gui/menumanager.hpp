#ifndef __LIB_MENUMANAGER_HPP__
#define __LIB_MENUMANAGER_HPP__

#include "theme.hpp"
#include <vector>
#include <lib/include/types.hpp>
#include <lib/draw/scene.hpp>

namespace lib
{
	namespace gui
	{
		class ChooseControl;
		class MenuManager
		{
		public:
			MenuManager(draw::SceneNode *sceneNode, str_const&& name, Theme theme = Theme{});
			virtual ~MenuManager();

			void setTheme(Theme theme) { m_theme = theme; }
			void addMenuSteps(const std::vector<sptr<ChooseControl>> &steps);
			void addMenuStep(sptr<ChooseControl> step);

			void start(const sptr<ChooseControl> &step);

			const Theme &currentTheme() const noexcept;

		private:
			void start(const sptr<ChooseControl> &firstStep);
			void changeStep(const sptr<ChooseControl> &step);
			void setActiveStep(const sptr<ChooseControl> &step);

			std::vector<sptr<ChooseControl>> m_steps;
			sptr<ChooseControl> m_activeMenuStep{ nullptr };
			Theme m_theme;
		};
	}
}

#endif
