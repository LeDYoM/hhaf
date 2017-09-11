#pragma once

#ifndef ZOPER_MAINMENU_INCLUDE_HPP__
#define ZOPER_MAINMENU_INCLUDE_HPP__

#include <lib/scene/nodes/choosecontrolgroup.hpp>
#include <lib/scene/scenenode.hpp>

namespace zoper
{
	class GameData;
	namespace zmenu
	{
		class MainMenu : public lib::scene::nodes::ChooseControlGroup
		{
		public:
			constexpr static const char*ClassName = "MainMenu";
			MainMenu(lib::scene::SceneNode *parent, lib::str name);
			virtual ~MainMenu();

			virtual void create() override;
			virtual void configure() override;

		private:
			lib::sptr<GameData> m_gameData;
			lib::sptr<lib::scene::nodes::ChooseControl> m_chooseControl;
		};
	}
}

#endif