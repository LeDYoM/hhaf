#include "gamescene.hpp"
#include "lib/board/boardmodel.hpp"
#include "lib/board/itilescontroller.hpp"

#include <SFML/Graphics.hpp>

namespace zoper
{
	GameScene::GameScene()
		: Scene("GameScene")
	{
	}


	GameScene::~GameScene()
	{
	}

	sf::Font font;
	sf::Text text;

	void GameScene::onEnterScene()
	{
		Scene::onEnterScene();
		p_boardModel = lib::sptr<lib::board::BoardModel>(new lib::board::BoardModel(10,10));

		font.loadFromFile("resources/fonts/sansation.ttf");

		// select the font
		text.setFont(font); // font is a sf::Font

		// set the string to display
		text.setString("Hello world");

		// set the character size
		text.setCharacterSize(24); // in pixels, not points!

		// set the color
		text.setColor(sf::Color::Red);

		// set the text style
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	}

	void GameScene::onExitScene()
	{
		p_boardModel = nullptr;
		Scene::onExitScene();
	}

	void GameScene::update()
	{

	}

}
