#pragma once

#ifndef __LIB_SCENE_CHOOSECONTROL_GROUP_INCLUDE_HPP__
#define __LIB_SCENE_CHOOSECONTROL_GROUP_INCLUDE_HPP__

#include "theme.hpp"
#include "statescontroller.hpp"
#include "optionmodel.hpp"
#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/scene.hpp>

namespace lib
{
	namespace input
	{
		enum Key;
	}
	namespace scene
	{
		namespace nodes
		{
			class ChooseControl;
			class ChooseControlGroup : public SceneNode
			{
			public:
				ChooseControlGroup(scene::SceneNode *parent, str name, Theme theme = Theme{});
				virtual ~ChooseControlGroup();

				virtual void create() override;
				virtual void configure() override;

				Property<Rectf32> box;
				void setTheme(const Theme &theme) { m_theme = theme; }

				Property<vector<vector<OptionModel>>> options;
				function<const OptionModelIndex(const OptionModelIndex&)> onSelected;
				const OptionModelIndex currentSelection() const noexcept;

				const Theme &currentTheme() const noexcept;
				Property<u32> currentControlIndex;

			private:
				uptr<StatesController> m_sController;
				Theme m_theme;
				ireceiver m_receiver;
			};
		}
	}
}

#endif
