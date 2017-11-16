#pragma once

#ifndef ZOPER_MAINMENU_INCLUDE_HPP__
#define ZOPER_MAINMENU_INCLUDE_HPP__

#include <lib/scene/scenenode.hpp>
#include "menupagetype.hpp"
#include "menupage.hpp"
#include <stack>

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

		void showPage(const MenuPageType&newPage);
		void hidePage(const MenuPageType&page);
		emitter<bool> MenuFinished;
	private:
		sptr<GameData> m_gameData;
		vector_shared_pointers<MenuPage> m_menuSteps;
		std::stack<MenuPageType> m_pagesStack;
	};
}

#endif