#include "gamescene.hpp"

#include "tile.hpp"
#include "player.hpp"

#include "lib/board/boardmodel.hpp"
#include "lib/board/itilescontroller.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/log.hpp"
#include "lib/compileconfig.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

namespace zoper
{
	GameScene::GameScene()
		: Scene("GameScene")
	{
		_gameData.size.x = 18;
		_gameData.size.y = 12;
		_gameData.centerRect.begin.x = 7;
		_gameData.centerRect.begin.y = 4;
		_gameData.centerRect.size.x = 4;
		_gameData.centerRect.size.y = 4;
		_gameData.generateTokenZones();
	}

	GameScene::~GameScene()
	{
	}

	sf::Font font;

	void GameScene::onInit()
	{
	}

	void GameScene::onDeinit()
	{
	}

	void GameScene::onEnterScene()
	{
		p_boardModel = lib::sptr<lib::board::BoardModel>(new lib::board::BoardModel(_gameData.size,this));

		font.loadFromFile("resources/fonts/sansation.ttf");

		getView()->setSize(10000, 10000);
		getView()->setCenter(5000, 5000);
		updateView();

		addPlayer();

		auto text = this->createText("hellow")->getAsText();

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

	void GameScene::onExitScene()
	{
		p_boardModel = nullptr;
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
		_tokenZones[0].y1 = centerRect.begin.y;
		_tokenZones[0].x2 = centerRect.begin.x - 1;
		_tokenZones[0].y2 = (centerRect.begin.y + centerRect.size.y) - 1;
		_tokenZones[0].horizontal = true;
		_tokenZones[0].increment = true;

		// From top to bottom
		_tokenZones[1].x1 = centerRect.begin.x;
		_tokenZones[1].y1 = 0;
		_tokenZones[1].x2 = (centerRect.begin.x + centerRect.size.x) - 1;
		_tokenZones[1].y2 = centerRect.begin.y - 1;
		_tokenZones[1].horizontal = false;
		_tokenZones[1].increment = true;

		// From right to left
		_tokenZones[2].x1 = size.x - 1;
		_tokenZones[2].y1 = centerRect.begin.y;
		_tokenZones[2].x2 = (centerRect.begin.x + centerRect.size.x);
		_tokenZones[2].y2 = (centerRect.begin.y + centerRect.size.y) - 1;
		_tokenZones[2].horizontal = true;
		_tokenZones[2].increment = false;

		// From bottom to top
		_tokenZones[3].x1 = centerRect.begin.x;
		_tokenZones[3].y1 = size.y - 1;
		_tokenZones[3].x2 = (centerRect.begin.x + centerRect.size.x) - 1;
		_tokenZones[3].y2 = centerRect.begin.y + centerRect.size.y;
		_tokenZones[3].horizontal = false;
		_tokenZones[3].increment = false;

		for (lib::u32 i = 0; i < NUMWAYS; ++i)
		{
			_tokenZones[i].size = _tokenZones[i].horizontal ? centerRect.size.y : centerRect.size.x;
			_tokenZones[i].incX = _tokenZones[i].horizontal ? (_tokenZones[i].increment ? -1 : 1) : 0;
			_tokenZones[i].incY = _tokenZones[i].horizontal ? 0 : (_tokenZones[i].increment ? -1 : 1);
		}
	}

	void GameScene::generateNextToken()
	{
		const GameData::TokenZone &currentTokenZone = _gameData._tokenZones[_nextTokenPart];

		LOG_DEBUG("NextTokenPart: " << std::to_string(_nextTokenPart));
		LOG_DEBUG("x1: " << currentTokenZone.x1 << " y1: " << currentTokenZone.y1 << " x2: " << currentTokenZone.x2 << " y2: " << currentTokenZone.y2);
//		LOG_DEBUG("distX: " << currentTokenZone.distX() << " distY: " << currentTokenZone.distY());
		LOG_DEBUG("horizontal: " << currentTokenZone.horizontal << " increment: " << currentTokenZone.increment);

		lib::u32 newToken = getRandomNumer(NUMTOKENS);

		lib::u32 sizep = getRandomNumer(currentTokenZone.size);

		lib::u32 newX = currentTokenZone.x1 + (currentTokenZone.horizontal ? 0 : sizep);
		lib::u32 newY = currentTokenZone.y1 + (currentTokenZone.horizontal ? sizep : 0);
		LOG_DEBUG("New tile pos: " << newX << "," << newY);

		lib::s32 x = currentTokenZone.horizontal ? currentTokenZone.x2 : newX;
		lib::s32 y = currentTokenZone.horizontal ? newY : currentTokenZone.y2;

		LOG_DEBUG("Starting at: " << x << "," << y);
		LOG_DEBUG("increment: " << currentTokenZone.incX << "," << currentTokenZone.incY);

		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		for (;
			p_boardModel->validCoords(lib::vector2du32(x, y)) && !pointInCenter(lib::vector2ds32(x, y));
			x += currentTokenZone.incX, y += currentTokenZone.incY)
		{
			p_boardModel->moveTile(lib::vector2du32(x, y), lib::vector2du32(x - currentTokenZone.incX, y - currentTokenZone.incY), true);
		}

		// Set the new token
		addNewToken(lib::vector2du32{ newX, newY }, newToken);
		_nextTokenPart = (_nextTokenPart + 1) % NUMWAYS;

		_debugDisplayBoard();
	}

	void GameScene::addPlayer()
	{
		LOG_DEBUG("Adding player tile at " << _gameData.centerRect.begin.x << "," << _gameData.centerRect.begin.y);
		__ASSERT(!p_player, "Player already initialized");
		// Create the player instance
		p_player = lib::sptr<Player>(new Player(lib::vector2du32(_gameData.centerRect.begin),tileSize(),_gameData.centerRect));
		// Set the position in the scene depending on the board position
		p_player->setPosition(board2Scene(p_player->boardPosition()));

		// Set the radius depending on the scene
//		p_player->getAsEllipseShape()->setSize(tileSize());

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(p_player->boardPosition(), std::dynamic_pointer_cast<lib::board::ITile>(addRenderizable(p_player)));
	}

	void GameScene::addNewToken(const lib::vector2du32 &position, lib::u32 newToken)
	{
		LOG_DEBUG("Adding new tile at " << position.x << "," << position.y << " with value " << newToken);
		// Create a new Tile instance
		auto newTileToken = lib::sptr<Tile>(new Tile(lib::board::BoardTileData(newToken),tileSize()));
		// Set the position in the scene depending on the board position
		newTileToken->setPosition(board2Scene(position));

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(position, std::dynamic_pointer_cast<lib::board::ITile>(addRenderizable(newTileToken)));
	}

	void GameScene::onKeyPressed(sf::Event::KeyEvent kEvent)
	{
		Scene::onKeyPressed(kEvent);
		p_player->onKeyPressed(kEvent);
	}

	void GameScene::onKeyReleased(sf::Event::KeyEvent kEvent)
	{
		Scene::onKeyReleased(kEvent);
		p_player->onKeyReleased(kEvent);
	}

	bool GameScene::pointInCenter(const lib::vector2ds32 &position) const
	{
		if (position.x < static_cast<lib::s32>(_gameData.centerRect.begin.x) || position.y < static_cast<lib::s32>(_gameData.centerRect.begin.y))
			return false;

		if (position.x >= static_cast<lib::s32>(_gameData.centerRect.begin.x + _gameData.centerRect.size.x) || position.y >= static_cast<lib::s32>(_gameData.centerRect.begin.y + _gameData.centerRect.size.y))
			return false;

		return true;
	}

	const lib::vector2df GameScene::board2Scene(const lib::vector2du32 &bPosition) const
	{
		const sf::View &view = *(this->getView());
		sf::Vector2f result{ view.getSize().x / static_cast<float>(p_boardModel->size().x), view.getSize().y / static_cast<float>(p_boardModel->size().y) };
		return lib::vector2df{ result.x * bPosition.x, result.y * bPosition.y };
	}

	const lib::vector2df GameScene::tileSize() const
	{
		return board2Scene(lib::vector2du32( 1, 1 ));
	}

	void GameScene::_debugDisplayBoard() const
	{
		for (lib::u32 y = 0; y < _gameData.size.y; ++y)
		{
			std::string temp;
			for (lib::u32 x = 0; x < _gameData.size.x; ++x)
			{
				std::string chTemp;
				auto lp_tile = p_boardModel->getTile(lib::vector2du32(x, y)).lock();
				if (lp_tile)
				{
					chTemp = std::to_string(lp_tile->getData());
				}
				else
				{
					chTemp = "*";
					if (pointInCenter(lib::vector2ds32(x, y)))
						chTemp = "C";
				}

				temp += chTemp;
			}
			LOG_DEBUG(temp);
		}
	}

	void GameScene::tileAppeared(const lib::vector2du32 &position, lib::board::WITilePointer tile)
	{
	}

	void GameScene::tileDissapeared(const lib::vector2du32 &position)
	{

	}

	void GameScene::tileSet(const lib::vector2du32 &position, lib::board::WITilePointer nTile)
	{
		lib::sptr<lib::board::ITile> snTile{ nTile };

		if (!snTile)
		{
			// Tile dissappeared
			tileDissapeared(position);
		}
		else
		{
			// Tile appeared
			tileAppeared(position, nTile);
		}

		// The rest (basically set from 0 to 0) should be ignored
	}

	void GameScene::tileMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::board::WITilePointer tile)
	{
		auto ztile = std::dynamic_pointer_cast<Tile>(tile.lock());
		ztile->getAsTransformable()->setPosition(board2Scene(dest));
	}
}
