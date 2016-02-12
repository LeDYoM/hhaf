#include "gamescene.hpp"

#include "tile.hpp"
#include "player.hpp"
#include "common.hpp"
#include <lib/board/boardmodel.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/core/log.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/draw/positionanimation.hpp>
#include <lib/draw/coloranimation.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
#include <memory>
#include <functional>

namespace zoper
{
	GameScene::GameScene()
		: Scene("GameScene"), Configuration("config.cfg"), _gameConfig{ ":NextGame" }
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

	void GameScene::onInit()
	{
		_mainBoardrg = this->createNewRenderGroup("mainBoard");
		_gameOverrg = this->createNewRenderGroup("gameOverScreen");
		_scorerg = this->createNewRenderGroup("score");
		_levelrg = this->createNewRenderGroup("level");
		_pauserg = this->createNewRenderGroup("pause");

		_scoreText = _scorerg->createText("scoretxt");
		_scoreDisplay = _scorerg->createText("scoredisplay");
		_currentLevelText = _scorerg->createText("scoretxt");
		_currentLevelDisplay = _scorerg->createText("scoredisplay");
		_levelText = _levelrg->createText("leveltxt");
		_levelDisplay = _levelrg->createText("leveldisplay");
		_goalText = _levelrg->createText("leveltxt");
		_goalDisplay = _levelrg->createText("leveldisplay");
		_pauseText = _pauserg->createText("pausetext");

		_gameText = _gameOverrg->createText("gameovergame");
		_overText = _gameOverrg->createText("gameoverover");

		_scoreText->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_scoreDisplay->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_currentLevelText->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_currentLevelDisplay->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_gameText->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_overText->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_levelText->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_levelDisplay->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_goalText->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_goalDisplay->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));
		_pauseText->setFont(*(resourceManager()->getResource("game_scene.scoreFont")->getAsFont()));

		_scoreText->setString("Score: ");
		increaseScore(0);
		_gameText->setString("GAME");
		_overText->setString("OVER");
		_pauseText->setString("PAUSE");
		_currentLevelText->setString("Level: ");
		_currentLevelDisplay->setString("0");

		_scoreText->setCharacterSize(90);
		_scoreDisplay->setCharacterSize(90);
		_currentLevelText->setCharacterSize(90);
		_currentLevelDisplay->setCharacterSize(90);
		_gameText->setCharacterSize(360);
		_overText->setCharacterSize(360);
		_levelText->setCharacterSize(90);
		_levelDisplay->setCharacterSize(90);
		_goalText->setCharacterSize(90);
		_goalDisplay->setCharacterSize(90);
		_pauseText->setCharacterSize(180);

		_scoreText->setColor(sf::Color::Blue);
		_scoreDisplay->setColor(sf::Color::White);
		_currentLevelText->setColor(sf::Color::Blue);
		_currentLevelDisplay->setColor(sf::Color::White);
		_gameText->setColor(sf::Color::White);
		_overText->setColor(sf::Color::White);
		_levelText->setColor(sf::Color::Blue);
		_levelDisplay->setColor(sf::Color::White);
		_goalText->setColor(sf::Color::Blue);
		_goalDisplay->setColor(sf::Color::White);
		_pauseText->setColor(sf::Color::White);

		_scoreText->setScale(1.0f, 2.0f);
		_scoreDisplay->setScale(1.0f, 2.0f);
		_levelText->setScale(1.0f, 2.0f);
		_levelDisplay->setScale(1.0f, 2.0f);
		_goalText->setScale(1.0f, 2.0f);
		_goalDisplay->setScale(1.0f, 2.0f);

		_scorerg->setPosition(50, 50);
		_scoreDisplay->setPositionX(_scoreText->getLocalBounds().width);

		_currentLevelDisplay->setPositionX(_currentLevelText->getLocalBounds().width);

		_levelrg->setPosition(1250, 50);
		_goalText->setPositionY(200);

		_currentLevelText->setPositionY(200);
		_currentLevelDisplay->setPositionY(200);


		auto _gameBoundingBox = _gameText->getLocalBounds();
		auto _overBoundingBox = _overText->getLocalBounds();
		auto sceneCenter = getCenterCoordinates();
		_gameText->setPosition(sceneCenter.x - (_gameBoundingBox.width / 2.0f), sceneCenter.y - _gameBoundingBox.height);
		_overText->setPosition(sceneCenter.x - (_overBoundingBox.width / 2.0f), sceneCenter.y);

		_pauseText->setPosition(sf::Vector2f{ 1000.0f, 1000.0f }, lib::scn::draw::Alignment::Center);

	}

	void GameScene::onDeinit()
	{
		// Remove instances from all nodes.
		clear();
	}

	void GameScene::onEnterScene()
	{
		p_boardModel = lib::sptr<lib::board::BoardModel>(new lib::board::BoardModel(_gameData.size, this));
		tilesCreated();
		addPlayer();
		_gameData._gameMode = static_cast<GameData::GameModes>(_gameConfig.getAsInt(GameModeStr, 0));

		_score = 0;
		_nextTokenPart = 0;
		setLevel(_gameConfig.getAsInt(StartLevelStr, 0));
		_gameOverrg->setVisible(false);
		_mainBoardrg->setVisible(true);
		_pauserg->setVisible(false);

		switch (_gameData._gameMode)
		{
		default:
		case GameData::GameModes::Token:
			_levelText->setString("Tokens: ");
			_goalText->setString("Goal: ");
			break;

		case GameData::GameModes::Time:
			_levelText->setString("Time: ");
			_goalText->setString("Goal: ");
			break;
		}

		_levelDisplay->setPositionX(_levelText->getLocalBounds().width);
		_goalDisplay->setPosition(sf::Vector2f{ _goalText->getLocalBounds().width, 200 });


		setState(Playing);

		gameClock.restart();
	}

	void GameScene::onExitScene()
	{
		_mainBoardrg->clear();
		p_boardModel = nullptr;
		p_player = nullptr;
		_backgroundTilesrg = nullptr;
		_backgroundTiles.clear();
	}

	void GameScene::update()
	{
		if (state() == Playing)
		{
			if (_gameData._gameMode == GameData::GameModes::Time)
				updateLevelData();

			if (gameClock.getElapsedTime().asMilliSeconds() > static_cast<lib::u64>(_levelProperties.millisBetweenTokens()))
			{
				// New token
				generateNextToken();
				gameClock.restart();
			}
		}
		else
		{
			
		}
	}

	bool GameScene::switchPause()
	{
		if (state() == Playing)
		{
			setState(Pause);
			_pauserg->setVisible(true);
			//_pauseText->getAsText()->setColor(sf::Color(255, 255, 255, 20));
			addAnimation(lib::scn::draw::anim::ColorAnimation::create(1000, _pauseText, sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 255)));
			gameClock.pause();
			return true;
		}
		else if (state() == Pause)
		{
			setState(Playing);
			_pauserg->setVisible(false);
			gameClock.resume();
			return false;
		}
		return false;
	}

	void GameScene::setLevel(const lib::u32 nv)
	{
		_levelProperties.setLevel(nv);
		LOG_DEBUG("Level set: " << _levelProperties.currentLevel());
		LOG_DEBUG("Millis between tokens: " << _levelProperties.millisBetweenTokens());
		LOG_DEBUG("Current base score: " << _levelProperties.baseScore());
		LOG_DEBUG("Seconds to next level: " << _levelProperties.stayTime());
		LOG_DEBUG("Tokens to next level: " << _levelProperties.stayTokens());

		_gameData.levelClock.restart();
		_gameData.consumedTokens = 0;

		// Update background tiles
		for (lib::u32 y = 0; y < _gameData.size.y; ++y)
		{
			for (lib::u32 x = 0; x < _gameData.size.x; ++x)
			{
				_backgroundTiles[y][x]->setColor(_levelProperties.getBackgroundTileColor(x, y, pointInCenter(lib::vector2du32{ x,y })));
				
			}
		}

		updateGoals();
		updateLevelData();
	}

	void GameScene::updateGoals()
	{
		_currentLevelDisplay->setString(std::to_string(_levelProperties.currentLevel()+1));

		switch (_gameData._gameMode)
		{
		default:
		case GameData::GameModes::Token:
			_goalDisplay->setString(std::to_string(_levelProperties.stayTokens()));
			break;

		case GameData::GameModes::Time:
			_goalDisplay->setString(std::to_string(_levelProperties.stayTime()));
			break;
		}
	}

	void GameScene::updateLevelData()
	{
		switch (_gameData._gameMode)
		{
		default:
		case GameData::GameModes::Token:
			_levelDisplay->setString(std::to_string(_gameData.consumedTokens));
			if (_gameData.consumedTokens >= _levelProperties.stayTokens())
				setLevel(_levelProperties.currentLevel() + 1);
			break;

		case GameData::GameModes::Time:
			_levelDisplay->setString(std::to_string(static_cast<lib::u16>(_gameData.levelClock.getElapsedTime().asSeconds())));
			if (_gameData.levelClock.getElapsedTime().asSeconds() >= _levelProperties.stayTime())
				setLevel(_levelProperties.currentLevel() + 1);
			break;
		}
	}

	void GameData::generateTokenZones()
	{
		// From left to right
		_tokenZones[0].zone.begin.x = 0;
		_tokenZones[0].zone.begin.y = centerRect.begin.y;
		_tokenZones[0].zone.size.x = centerRect.begin.x - 1;
		_tokenZones[0].zone.size.y = (centerRect.begin.y + centerRect.size.y) - 1;
		_tokenZones[0].direction = Direction::DirectionData::Right;

		// From top to bottom
		_tokenZones[1].zone.begin.x = centerRect.begin.x;
		_tokenZones[1].zone.begin.y = 0;
		_tokenZones[1].zone.size.x = (centerRect.begin.x + centerRect.size.x) - 1;
		_tokenZones[1].zone.size.y = centerRect.begin.y - 1;
		_tokenZones[1].direction = Direction::DirectionData::Down;

		// From right to left
		_tokenZones[2].zone.begin.x = size.x - 1;
		_tokenZones[2].zone.begin.y = centerRect.begin.y;
		_tokenZones[2].zone.size.x = (centerRect.begin.x + centerRect.size.x);
		_tokenZones[2].zone.size.y = (centerRect.begin.y + centerRect.size.y) - 1;
		_tokenZones[2].direction = Direction::DirectionData::Left;

		// From bottom to top
		_tokenZones[3].zone.begin.x = centerRect.begin.x;
		_tokenZones[3].zone.begin.y = size.y - 1;
		_tokenZones[3].zone.size.x = (centerRect.begin.x + centerRect.size.x) - 1;
		_tokenZones[3].zone.size.y = centerRect.begin.y + centerRect.size.y;
		_tokenZones[3].direction = Direction::DirectionData::Up;

		for (lib::u32 i = 0; i < NUMWAYS; ++i)
		{
			_tokenZones[i].size = _tokenZones[i].direction.isHorizontal() ? centerRect.size.y : centerRect.size.x;
		}
	}

	void GameScene::generateNextToken()
	{
		const GameData::TokenZone &currentTokenZone = _gameData._tokenZones[_nextTokenPart];

		LOG_DEBUG("NextTokenPart: " << std::to_string(_nextTokenPart));
		LOG_DEBUG("x1: " << currentTokenZone.zone.begin.x << " y1: " << currentTokenZone.zone.begin.y << 
			" x2: " << currentTokenZone.zone.size.x << " y2: " << currentTokenZone.zone.size.y);

		lib::u32 newToken = 0;// getRandomNumer(NUMTOKENS);

		lib::u32 sizep = 0;// getRandomNumer(currentTokenZone.size);

		lib::u32 newX = currentTokenZone.zone.begin.x + (currentTokenZone.direction.isHorizontal() ? 0 : sizep);
		lib::u32 newY = currentTokenZone.zone.begin.y + (currentTokenZone.direction.isHorizontal() ? sizep : 0);
		LOG_DEBUG("New tile pos: " << newX << "," << newY);

		lib::vector2du32 loopPosition{ (currentTokenZone.direction.isHorizontal() ? currentTokenZone.zone.size.x : newX),
			(currentTokenZone.direction.isHorizontal() ? newY : currentTokenZone.zone.size.y) };
//		lib::vector2du32 destPosition;
		LOG_DEBUG("Starting at: " << loopPosition.x << "," << loopPosition.y);

		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		Direction loopDirection = currentTokenZone.direction.negate();
		for_each_token_in_line(loopPosition, loopDirection, [this](const lib::vector2du32 &loopPosition, const Direction &direction)
		{
			if (!p_boardModel->tileEmpty(loopPosition))
			{
				lib::vector2du32 dest = direction.negate().applyToVector(loopPosition);
				p_boardModel->moveTile(loopPosition, dest);

				if (pointInCenter(dest))
				{
					startGameOver();
				}
			}
			return true;
		});
		// Set the new token
		addNewToken(lib::vector2du32{ newX, newY }, newToken);
		_nextTokenPart = (_nextTokenPart + 1) % NUMWAYS;

		EXECUTE_IN_DEBUG(_debugDisplayBoard());
	}

	void GameScene::startGameOver()
	{
		setState(GameOver);
		_gameOverrg->setVisible(true);
	}

	void GameScene::for_each_token_in_line(const lib::vector2du32 &startPosition, const Direction &direction,
		std::function<bool(const lib::vector2du32 &, const Direction &)> updatePredicate)
	{
		lib::vector2du32 loopPosition{ startPosition };
		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		bool stay{ true };
		do
		{
			stay &= updatePredicate(loopPosition, direction);
			loopPosition = direction.applyToVector(loopPosition);
			stay &= p_boardModel->validCoords(loopPosition);
		} while (stay);
	}

	void GameScene::addPlayer()
	{
		LOG_DEBUG("Adding player tile at " << _gameData.centerRect.begin.x << "," << _gameData.centerRect.begin.y);
		__ASSERT(!p_player, "Player already initialized");
		// Create the player instance
		p_player = lib::sptr<Player>(new Player(lib::vector2du32(_gameData.centerRect.begin),tileSize()));

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(p_player->boardPosition(), std::dynamic_pointer_cast<lib::board::ITile>(_mainBoardrg->addRenderizable(p_player)));
	}

	void GameScene::addNewToken(const lib::vector2du32 &position, lib::u32 newToken)
	{
		LOG_DEBUG("Adding new tile at " << position.x << "," << position.y << " with value " << newToken);
		// Create a new Tile instance
		lib::sptr<Tile> newTileToken = lib::sptr<Tile>(new Tile(lib::board::BoardTileData(newToken),tileSize()));
		// Set the position in the scene depending on the board position
		newTileToken->setPosition(board2Scene(position));

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(position, std::dynamic_pointer_cast<lib::board::ITile>(_mainBoardrg->addRenderizable(newTileToken)));
	}

	void GameScene::onKeyPressed(sf::Event::KeyEvent kEvent)
	{
		Scene::onKeyPressed(kEvent);
		switch (state())
		{
		case Playing:
		{
			auto dir = _keyMapping.getDirectionFromKey(kEvent.code);
			if (dir.isValid())
			{
				p_player->setCurrentDirection(dir);
				movePlayer(dir);
			}
			else if (_keyMapping.isLaunchKey(kEvent.code))
			{
				launchPlayer();
			}
			else if (_keyMapping.isPauseKey(kEvent.code))
			{
				switchPause();
			}
		}
		break;
		case GameOver:
			setNextScene("MenuScene");
			break;
		case Pause:
			if (_keyMapping.isPauseKey(kEvent.code))
			{
				switchPause();
			}
			break;
		}
	}

	void GameScene::movePlayer(const Direction & dir)
	{
		__ASSERT(dir.isValid(), "Invalid direction passed to move");
		auto nPosition = dir.applyToVector(p_player->boardPosition());
		if (pointInCenter(nPosition))
		{
			p_boardModel->moveTile(p_player->boardPosition(), lib::vector2du32(nPosition.x,nPosition.y));
			p_player->setBoardPosition(lib::vector2du32(nPosition.x, nPosition.y));
		}
		else
		{
			updatePlayer(p_player->boardPosition(), p_player);
		}
	}

	void GameScene::onKeyReleased(sf::Event::KeyEvent kEvent)
	{
		Scene::onKeyReleased(kEvent);
	}

	void GameScene::onAnimationStarted(lib::sptr<lib::scn::draw::anim::IAnimation> anim, lib::sptr<lib::scn::draw::Renderizable> node)
	{
	}

	void GameScene::onAnimationFinished(lib::sptr<lib::scn::draw::anim::IAnimation> anim, lib::sptr<lib::scn::draw::Renderizable> node)
	{
		if (anim->animationType() == "ColorAnimation" && node == _pauseText)
		{
			_pauserg->setVisible(state()==Pause);
			_pauseText->setColor(sf::Color::White);
		}
		else if (anim->animationType() == "PositionAnimation" && node->name() == "pointIncrementScore")
		{
			removeRenderizable(node);
		}
	}

	void GameScene::launchPlayer()
	{
		LOG_DEBUG("Launching player");
		const Direction loopDirection = p_player->currentDirection();
		lib::vector2du32 loopPosition{ p_player->boardPosition() };
		lib::board::BoardTileData tokenType = p_player->getData();
		lib::u32 inARow{ 0 };
		for_each_token_in_line(loopPosition, loopDirection, [this,tokenType,&inARow](const lib::vector2du32 &loopPosition, const Direction &direction)
		{
			direction;
			bool result{ true };
			bool found{ false };
			sf::Vector2f lastTokenPosition;

			if (!p_boardModel->tileEmpty(loopPosition) && !pointInCenter(loopPosition) && result)
			{
				lib::sptr<lib::board::ITile> currentToken{ p_boardModel->getTile(loopPosition).lock() };
				lib::board::BoardTileData currentTokenType = currentToken->getData();
				if (currentTokenType == tokenType)
				{
					++inARow;
					increaseScore(inARow*_levelProperties.baseScore());
					_gameData.consumedTokens++;
					lastTokenPosition = board2Scene(loopPosition);
					p_boardModel->deleteTile(loopPosition);
					found = true;
				}
				else
				{
					p_boardModel->changeTileData(p_player->boardPosition(), currentTokenType);
					p_boardModel->changeTileData(loopPosition, tokenType);
					LOG_DEBUG("Player type changed to " << p_player->getData());
					result = false;
				}
			}
			if (found)
			{
				auto node = createShape("pointIncrementScore", sf::Vector2f{ 15.0f,15.0f });
				addAnimation(lib::scn::draw::anim::PositionAnimation::create(600, node, lastTokenPosition, lib::vector2df(450,100)));
			}
			return result;
		});

		if (_gameData._gameMode == GameData::GameModes::Token)
			updateLevelData();
	}

	bool GameScene::pointInCenter(const lib::vector2du32 &position) const
	{
		if (p_boardModel->validCoords(position))
		{
			if (position.x < _gameData.centerRect.begin.x || position.y < _gameData.centerRect.begin.y)
				return false;

			if (position.x >= (_gameData.centerRect.begin.x + _gameData.centerRect.size.x) || position.y >= (_gameData.centerRect.begin.y + _gameData.centerRect.size.y))
				return false;

			return true;
		}
		return false;
	}

	const lib::vector2df GameScene::board2Scene(const lib::vector2du32 &bPosition) const
	{
		return lib::vector2df{ (getView()->getSize().x * bPosition.x) / static_cast<float>(p_boardModel->size().x),
			(getView()->getSize().y * bPosition.y) / static_cast<float>(p_boardModel->size().y) };
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
					if (pointInCenter(lib::vector2du32(x, y)))
						chTemp = "C";
				}

				temp += chTemp;
			}
			LOG_DEBUG(temp);
		}
	}

	void GameScene::tilesCreated()
	{
		_backgroundTilesrg = createNewRenderGroup("backgroundTiles", _mainBoardrg);
		for (lib::u32 y = 0; y < _gameData.size.y; ++y)
		{
			std::vector<lib::sptr<lib::scn::draw::NodeShape>> column;

			for (lib::u32 x = 0; x < _gameData.size.x; ++x)
			{
				auto tileBackground = _backgroundTilesrg->createSpriteShape("backgroundTile", tileSize());
				tileBackground->setPosition(board2Scene(lib::vector2du32{ x,y }));
				column.push_back(tileBackground);

				auto node = _backgroundTilesrg->createShape("backgroundTilePoint", sf::Vector2f{ 10.0f,10.0f });
				sf::Vector2f center( board2Scene(lib::vector2du32{ x,y }) );
				center.x += tileSize().x / 2.0f;
				center.y += tileSize().y / 2.0f;
				center.x -= (node->getLocalBounds().width / 2.0f);
				center.y -= (node->getLocalBounds().height / 2.0f);
				node->setPosition(center);
				node->setColor(sf::Color::White);
			}
			_backgroundTiles.push_back(column);
		}
	}

	void GameScene::tileAdded(const lib::vector2du32 &position, lib::board::WITilePointer nTile)
	{
		// Tile appeared
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile.lock()))
		{
			tokenAppeared(position, ztile);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile.lock()))
		{
			// Set the position in the scene depending on the board position
			playerAppeared(position, ztile_);
		}
	}

	void GameScene::tileDeleted(const lib::vector2du32 &position, lib::board::WITilePointer nTile)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile.lock()))
		{
			tokenDissapeared(position,ztile);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile.lock()))
		{
			playerDissapeared(position,ztile_);
		}
	}

	void GameScene::tileMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::board::WITilePointer tile)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(tile.lock()))
		{
			tokenMoved(source, dest, ztile);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(tile.lock()))
		{
			playerMoved(source, dest, ztile_);
		}
	}

	void GameScene::tileChanged(const lib::vector2du32 &position, lib::board::WITilePointer nTile, 
		const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile.lock()))
		{
			tokenChangedValue(position, ztile, ov, nv);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile.lock()))
		{
			playerChangedValue(position, ztile_, ov, nv);
		}
	}

	void GameScene::tokenMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Tile> tile)
	{
		source;
		addAnimation(lib::scn::draw::anim::PositionAnimation::create(_levelProperties.millisBetweenTokens() / 2, tile, board2Scene(dest)));
	}

	void GameScene::tokenAppeared(const lib::vector2du32 &position, lib::sptr<Tile> tile)
	{
		position;
		tile;
	}

	void GameScene::tokenDissapeared(const lib::vector2du32 &position, lib::sptr<Tile> tile)
	{
		position;
		LOG_DEBUG("Deleting token " << tile->name() << " from scene");
		_mainBoardrg->removeRenderizable(tile);
	}

	void GameScene::tokenChangedValue(const lib::vector2du32 &position, lib::sptr<Tile> tile,
		const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv)
	{
		position; nv; ov;
		tile->setColor(tile->getColorForToken());
	}

	void GameScene::updatePlayer(const lib::vector2du32 &dest, lib::sptr<Player> player_)
	{
		player_->setOrigin(tileSize() / 2.0f);
		player_->setPosition(board2Scene(dest) + (tileSize() / 2.0f));
		player_->setRotation(player_->currentDirection().angle());
	}

	void GameScene::playerMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Player> player_)
	{
		source;
		updatePlayer(dest, player_);
	}

	void GameScene::playerAppeared(const lib::vector2du32 &position, lib::sptr<Player> player)
	{
		player->setPosition(board2Scene(position));
	}

	void GameScene::playerDissapeared(const lib::vector2du32 &position, lib::sptr<Player> player)
	{
		position;

	}

	void GameScene::playerChangedValue(const lib::vector2du32 &position, lib::sptr<Player> player,
		const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv)
	{
		position; nv; ov;
		player->setColor(player->getColorForToken());
	}

	void GameScene::increaseScore(lib::u32 scoreIncrement)
	{
		_score += scoreIncrement;
		std::string result{ std::to_string(_score) };
		while (result.size() < _scoreSize) result = "0" + result;
		_scoreDisplay->setString(result);
	}

	const lib::vector2df GameScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}
}
