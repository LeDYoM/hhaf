#ifndef __LIB_CHOOSECONTROL_GROUP_INCLUDE_HPP__
#define __LIB_CHOOSECONTROL_GROUP_INCLUDE_HPP__

#pragma once

#include "theme.hpp"
#include "statescontroller.hpp"
#include <vector>
#include <lib/include/types.hpp>
#include <lib/draw/scene.hpp>
#include <lib/gui/optionmodel.hpp>

namespace lib
{
	namespace gui
	{
		class ChooseControl;
		class ChooseControlGroup : public draw::SceneNode
		{
		public:
			ChooseControlGroup(draw::SceneNode *parent, str_const&& name, Theme theme = Theme{});
			virtual ~ChooseControlGroup();

			virtual void create() override;
			virtual void configure() override;
			void setTheme(const Theme &theme) { m_theme = theme; }
			void addChooseControls(const std::vector<sptr<ChooseControl>> &steps);
			void addChooseControl(sptr<ChooseControl> step);

			void start(const std::string &firstStep);
			Property<std::vector<std::vector<OptionModel>>> options;
			Property<std::vector<std::function<void(const u32)>>> onSelected;

			const Theme &currentTheme() const noexcept;
			Property<u32> currentControlIndex;

		private:
			uptr<StatesController> m_sController;
			Theme m_theme;
		};
	}
}

#endif
