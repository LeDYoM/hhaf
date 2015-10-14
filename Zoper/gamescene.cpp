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
		_gameData.width = 18;
		_gameData.height = 12;
		_gameData.centerQuadx = 7;
		_gameData.centerQuady = 4;
		_gameData.centerQuadw = 4;
		_gameData.centerQuadh = 4;
		_gameData.generateTokenZones();
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

	void GameData::generateTokenZones()
	{
		// From left to right
		_tokenZones[0].x1 = 0;
		_tokenZones[0].y1 = centerQuady;
		_tokenZones[0].x2 = centerQuadx - 1;
		_tokenZones[0].y2 = centerQuady + centerQuadh - 1;
		_tokenZones[0].horizontal = true;

		// From top to bottom
		_tokenZones[1].x1 = centerQuadx;
		_tokenZones[1].y1 = 0;
		_tokenZones[1].x2 = centerQuadx + (centerQuadw - 1);
		_tokenZones[1].y2 = centerQuady - 1;
		_tokenZones[1].horizontal = false;

		// From right to left
		_tokenZones[2].x1 = width - 1;
		_tokenZones[2].y1 = centerQuady;
		_tokenZones[2].x2 = centerQuadx + centerQuadw;
		_tokenZones[2].y2 = centerQuady - centerQuadh - 1;
		_tokenZones[2].horizontal = true;

		// From bottom to top
		_tokenZones[3].x1 = centerQuadx;
		_tokenZones[3].y1 = height - 1;
		_tokenZones[3].x2 = centerQuadx + (centerQuadw - 1);
		_tokenZones[3].y2 = centerQuady + (centerQuadh - 1);
		_tokenZones[3].horizontal = false;
	}

	void GameScene::generateNextToken()
	{
		const GameData::TokenZone &currentTokenZone = _gameData._tokenZones[_nextTokenPart];

		LOG_DEBUG("NextTokenPart: " << std::to_string(_nextTokenPart));
		LOG_DEBUG("x1: " << currentTokenZone.x1 << " y1: " << currentTokenZone.y1 << " x2: " << currentTokenZone.x2 << " y2: " << currentTokenZone.y2);
		LOG_DEBUG("distX: " << currentTokenZone.distX() << " distY: " << currentTokenZone.distY());
		LOG_DEBUG("horizontal: " << currentTokenZone.horizontal << " increment: " << currentTokenZone.increment());

		lib::s32 newToken = getRandomNumer(5, 1);
		lib::s32 size,sizep;

		size = currentTokenZone.horizontal ? _gameData.centerQuadh : _gameData.centerQuadw;
		sizep = getRandomNumer(size, 0);

		lib::s32 newX = currentTokenZone.x1 + currentTokenZone.horizontal ? 0 : sizep;
		lib::s32 newY = currentTokenZone.y1 + currentTokenZone.horizontal ? sizep : 0;
		LOG_DEBUG("New tile pos: " << newX << "," << newY);

		lib::s32 x = currentTokenZone.x2;
		lib::s32 y = currentTokenZone.y2;

		lib::s32 incX = currentTokenZone.horizontal ? (currentTokenZone.increment()?-1:1) : 0;
		lib::s32 incY = currentTokenZone.horizontal ? 0 :(currentTokenZone.increment() ? -1 : 1);

		LOG_DEBUG("Starting at: " << x << "," << y);
		LOG_DEBUG("increment: " << incX << "," << incY);

		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		for (;
			pointInBounds(x, y) && !pointInCenter(x, y);
			x += incX, y += incY)
		{
			p_boardModel->moveTile(x, y, x - incX, y - incY);
		}

		// Set the new token
		LOG_DEBUG("Adding new tile at " << currentTokenZone.x1 + newX << "," << currentTokenZone.y1 + newY << " with value "<<newToken);
		p_boardModel->setTile(currentTokenZone.x1 + newX, currentTokenZone.y1 + newY, newToken);
		_nextTokenPart = (_nextTokenPart + 1) % 4;

		_debugDisplayBoard();
	}

	bool GameScene::pointInBounds(lib::s32 x, lib::s32 y) const
	{
		if (x < 0 || y < 0)
			return false;

		if (x >= static_cast<lib::s32>(_gameData.width) || y >= static_cast<lib::s32>(_gameData.height))
			return false;

		return true;
	}

	bool GameScene::pointInCenter(lib::s32 x, lib::s32 y) const
	{
		if (x < static_cast<lib::s32>(_gameData.centerQuadx) || y < static_cast<lib::s32>(_gameData.centerQuady))
			return false;

		if (x >= static_cast<lib::s32>(_gameData.centerQuadx + _gameData.centerQuadw) || y >= static_cast<lib::s32>(_gameData.centerQuady + _gameData.centerQuadh))
			return false;

		return true;
	}

	void GameScene::onExitScene()
	{
		p_boardModel = nullptr;
		Scene::onExitScene();
	}

	void GameScene::_debugDisplayBoard() const
	{
		for (lib::u32 y = 0; y < _gameData.height; ++y)
		{
			std::string temp;
			for (lib::u32 x = 0; x < _gameData.width; ++x)
			{
				std::string chTemp = std::to_string(p_boardModel->getTile(x,y));
				if (pointInCenter(x, y))
					chTemp = "C";
				temp += chTemp;
			}
			LOG_DEBUG(temp);
		}
	}

}
