#ifndef __LIB_CHOOSECONTROL_GROUP_INCLUDE_HPP__
#define __LIB_CHOOSECONTROL_GROUP_INCLUDE_HPP__

#pragma once

#include "theme.hpp"
#include <vector>
#include <lib/include/types.hpp>
#include <lib/draw/scene.hpp>

namespace lib
{
	namespace gui
	{
		class ChooseControl;
		class ChooseControlGroup : public draw::Scene
		{
		public:
			ChooseControlGroup(str_const&& name, Theme theme = Theme{});
			virtual ~ChooseControlGroup();

			void setTheme(Theme theme) { m_theme = theme; }
			void addMenuSteps(const std::vector<sptr<ChooseControl>> &steps);
			void addMenuStep(sptr<ChooseControl> step);

			void start(const std::string &firstStep);
			void changeStep(const std::string &step);

			const Theme &currentTheme() const noexcept;

		private:
			void start(sptr<ChooseControl> &firstStep);
			void changeStep(sptr<ChooseControl> &step);
			void setActiveStep(sptr<ChooseControl> &step);

			std::vector<sptr<ChooseControl>> m_steps;
			sptr<ChooseControl> m_activeMenuStep{ nullptr };
			Theme m_theme;
		};
	}
}

#endif
