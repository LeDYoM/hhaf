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

			bool changeState(const OptionModelIndex&);
			void setTheme(const Theme &theme) { m_theme = theme; }

			Property<std::vector<std::vector<OptionModel>>> options;
			std::function<const OptionModelIndex(const OptionModelIndex&)> onSelected;
			const std::vector<u32> currentSelection() const noexcept;

			const Theme &currentTheme() const noexcept;
			Property<u32> currentControlIndex;

		private:
			uptr<StatesController> m_sController;
			Theme m_theme;
		};
	}
}

#endif
