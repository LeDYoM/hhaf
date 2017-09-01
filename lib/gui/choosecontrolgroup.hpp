#ifndef __LIB_CHOOSECONTROL_GROUP_INCLUDE_HPP__
#define __LIB_CHOOSECONTROL_GROUP_INCLUDE_HPP__

#pragma once

#include "theme.hpp"
#include "statescontroller.hpp"
#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/scene.hpp>
#include <lib/gui/optionmodel.hpp>

namespace lib
{
	namespace gui
	{
		class ChooseControl;
		class ChooseControlGroup : public scene::SceneNode
		{
		public:
			ChooseControlGroup(scene::SceneNode *parent, str name, Theme theme = Theme{});
			virtual ~ChooseControlGroup();

			virtual void create() override;
			virtual void configure() override;

			Property<Rectf32> box;
			void setTheme(const Theme &theme) { m_theme = theme; }

			Property<vector<vector<OptionModel>>> options;
			lib::function<const OptionModelIndex(const OptionModelIndex&)> onSelected;
			const OptionModelIndex currentSelection() const noexcept;

			const Theme &currentTheme() const noexcept;
			Property<u32> currentControlIndex;

		private:
			uptr<StatesController> m_sController;
			Theme m_theme;
		};
	}
}

#endif
