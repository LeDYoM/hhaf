#pragma once

#ifndef ZOPER_MAINMENU_INCLUDE_HPP__
#define ZOPER_MAINMENU_INCLUDE_HPP__

#include <lib/scene/scenenode.hpp>
#include "menupagetype.hpp"
#include "menupage.hpp"

namespace zoper
{
	class GameData;
	using namespace lib;

	class MainMenu : public scene::SceneNode
	{
	public:
		static constexpr char ClassName[] = "MainMenu";
		MainMenu(scene::SceneNode *parent, str name);
		virtual ~MainMenu();

		virtual void onCreated() override;

		void showPage(const MenuPageType&newPage);
		void hidePage(const MenuPageType&page);
		emitter<> MenuFinished;
	private:
		sptr<GameData> m_gameData;
		vector_shared_pointers<MenuPage> m_menuSteps;
	};
}

#endif