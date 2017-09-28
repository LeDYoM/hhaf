#pragma once

#ifndef ZOPER_MAINMENU_INCLUDE_HPP__
#define ZOPER_MAINMENU_INCLUDE_HPP__

#include <lib/scene/scenenode.hpp>

namespace zoper
{
	class GameData;
	using namespace lib;
	class MainMenu : public scene::SceneNode
	{
	public:
		constexpr static const char*ClassName = "MainMenu";
		MainMenu(scene::SceneNode *parent, str name);
		virtual ~MainMenu();

		virtual void create() override;
		virtual void configure() override;

	private:
		sptr<GameData> m_gameData;
		vector_shared_pointers<scene::nodes::ChooseControl> m_menuSteps;
		sptr<scene::nodes::ChooseControl> m_chooseControl;
	};
}

#endif