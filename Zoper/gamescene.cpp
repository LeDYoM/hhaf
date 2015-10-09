#include "gamescene.hpp"
#include "lib/board/boardmodel.hpp"
#include "lib/board/itilescontroller.hpp"
#include "lib/log.hpp"
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

	void GameScene::onEnterScene()
	{
		Scene::onEnterScene();
		p_boardModel = lib::sptr<lib::board::BoardModel>(new lib::board::BoardModel(_gameData.width,_gameData.height));

		font.loadFromFile("resources/fonts/sansation.ttf");

		auto text = this->createText("hellow");

		// select the font
		text->setFont(font); // font is a sf::Font

		// set the string to display
		text->setString("Hello world");

		// set the character size
		text->setCharacterSize(24); // in pixels, not points!

		// set the color
		text->setColor(sf::Color::Red);

		// set the text style
		text->setStyle(sf::Text::Bold | sf::Text::Underlined);

		text->setPosition(500, 500);

		clock.restart();
	}

	void GameScene::update()
	{
		if (clock.getElapsedTime().asMilliseconds() > _millisBetweenTokens)
		{
			// New token
		}
	}

	void GameScene::generateNextToken()
	{
		lib::u32 startX, startY;
		lib::s8 directionX,directionY;
		switch (_nextTokenPart)
		{
		case 0:
			// From left to right
			startX = 0;
			startY = _gameData.centerQuady;
			directionX = directionY = 1;
			break;
		case 1:
			// From top to bottom
			startX = _gameData.centerQuadx;
			startY = 0;
			directionX = 1;
			directionY = 1;
			break;
		case 2:
			// From right to left
			startX = _gameData.width - 1;
			startY = _gameData.centerQuady;
			directionX = -1;
			directionY = 1;
			break;
		case 3:
			// From bottom to top
			startX = _gameData.centerQuadx;
			startY = 0;
			directionX = 1;
			directionY = 1;
			break;
		default:
			__ASSERT(false, "Error");
			break;
		}
	}

	void GameScene::onExitScene()
	{
		p_boardModel = nullptr;
		Scene::onExitScene();
	}
}
