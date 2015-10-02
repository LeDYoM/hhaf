#include "menuscene.hpp"

namespace zoper
{
	MenuScene::MenuScene()
		: Scene("MenuScene")
	{
	}


	MenuScene::~MenuScene()
	{
	}

	void MenuScene::onActivated()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void MenuScene::onDeactivated()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}
