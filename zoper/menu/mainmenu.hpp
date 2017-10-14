#pragma once

#ifndef ZOPER_MAINMENU_INCLUDE_HPP__
#define ZOPER_MAINMENU_INCLUDE_HPP__

#include <lib/scene/scenenode.hpp>
#include "menupage.hpp"

namespace zoper
{
	class GameData;
	using namespace lib;

	enum class MenuPageType
	{
		Main,
		SelectLevelToken,
		SelectLevelSpeed,
		Options
	};

	class MainMenu : public scene::SceneNode
	{
	public:
		constexpr static const char*ClassName = "MainMenu";
		MainMenu(scene::SceneNode *parent, str name);
		virtual ~MainMenu();

		virtual void create() override;
		virtual void configure() override;

		void mainMenuPageChanged(const MenuPageType&newPage, const MenuPageType&oldPage);
	private:
		sptr<GameData> m_gameData;
		vector_shared_pointers<MenuPage> m_menuSteps;
	};
}

#endif