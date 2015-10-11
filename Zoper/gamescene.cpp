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
			generateNextToken();
			clock.restart();
		}
	}

	void GameScene::generateNextToken()
	{
		lib::u32 startX, startY;
		bool horizontal, positive;
		switch (_nextTokenPart)
		{
		case 0:
			// From left to right
			startX = _gameData.centerQuadx;
			startY = _gameData.centerQuady;
			horizontal = true;
			positive = false;
			break;
		case 1:
			// From top to bottom
			startX = _gameData.centerQuadx;
			startY = _gameData.centerQuady;
			horizontal = false;
			positive = false;
			break;
		case 2:
			// From right to left
			startX = _gameData.centerQuadx + _gameData.centerQuadw;
			startY = _gameData.centerQuady;
			horizontal = true;
			positive = false;
			break;
		case 3:
			// From bottom to top
			startX = _gameData.centerQuadx;
			startY = _gameData.centerQuady + _gameData.centerQuadh;
			horizontal = false;
			positive = true;
			break;
		default:
			__ASSERT(false, "Error");
			break;
		}

		LOG_DEBUG("startX: " << startX << " starty: "<<startY<<" horizontal: "<<horizontal<<" poitive: "<<positive);
		lib::s32 newToken = getRandomNumer(5, 0);
		lib::s32 size,sizep;

		size = horizontal ? _gameData.centerQuadh : _gameData.centerQuadw;
		sizep = getRandomNumer(size, 0);

		lib::u32 beginX, beginY;
		lib::u32 incX, incY;

		if (horizontal)
		{
			beginX = startX;
			beginY = startY + sizep;
			incX = (positive ? 1 : -1);
			incY = 0;
		}
		else
		{
			beginX = startX + sizep;
			beginY = startY;
			incX = 0;
			incY = (positive ? 1 : -1);
		}


		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		for (lib::u32 x = beginX, y = beginY;
			!pointInBounds(x, y);
			x += incX, y += incY)
		{
			if (p_boardModel->getTile(x, y) != 0)
			{

			}
		}
	}

	bool GameScene::pointInBounds(lib::u32 x, lib::u32 y) const
	{
		if (x < _gameData.centerQuadx || y < _gameData.centerQuady)
			return false;

		if (x > _gameData.centerQuadx + _gameData.centerQuadw || y > _gameData.centerQuady + _gameData.centerQuadh)
			return false;

		return true;
	}

	void GameScene::onExitScene()
	{
		p_boardModel = nullptr;
		Scene::onExitScene();
	}
}
