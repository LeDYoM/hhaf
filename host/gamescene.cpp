#include "gamescene.hpp"

#include "tile.hpp"
#include "player.hpp"
#include "common.hpp"
#include <lib/board/boardmodel.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/core/log.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/draw/positionanimation.hpp>
#include <lib/draw/coloranimation.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodequad.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/inputevent.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::draw;

	GameScene::GameScene()
		: Scene("GameScene"), Configuration("config.cfg"), _gameConfig{ ":NextGame" }
	{
		_gameData.size.x = 18;
		_gameData.size.y = 12;
		_gameData.centerRect = Rectu32{ 7,4,4,4 };
		_gameData.generateTokenZones();
	}

	GameScene::~GameScene()
	{
	}

	void GameScene::onInit()
	{
		Scene::onInit();
		_mainBoardrg = this->createNewRenderGroup("mainBoard");
		_gameOverrg = this->createNewRenderGroup("gameOverScreen");
		_scorerg = this->createNewRenderGroup("score");
		_levelrg = this->createNewRenderGroup("level");
		_pauserg = this->createNewRenderGroup("pause");

		auto& resourceManager{ lib::host().resourceManager() };
		auto scoreFont(resourceManager.getFont("game_scene.scoreFont"));
		_scoreText = _scorerg->createText("scoretxt", "Score: ", scoreFont, 90, colors::Blue);
		_scoreDisplay = _scorerg->createText("scoredisplay", "", scoreFont, 90, colors::White);
		_currentLevelText = _scorerg->createText("currentLevelText", "Level: ", scoreFont, 90, colors::Blue);
		_currentLevelDisplay = _scorerg->createText("currentLevelDisplay", "0", scoreFont, 90, colors::White);
		_levelText = _levelrg->createText("leveltxt", "", scoreFont, 90, colors::Blue);
		_levelDisplay = _levelrg->createText("leveldisplay", "", scoreFont, 90, colors::White);
		_goalText = _levelrg->createText("goalText", "", scoreFont, 90, colors::Blue);
		_goalDisplay = _levelrg->createText("goalDisplay", "", scoreFont, 90, colors::White);
		_pauseText = _pauserg->createText("pausetext", "PAUSE", scoreFont, 180, colors::White);

		_gameText = _gameOverrg->createText("gameovergame", "GAME", scoreFont, 360, colors::White);
		_overText = _gameOverrg->createText("gameoverover", "OVER", scoreFont, 360, colors::White);

		increaseScore(0);

		_scoreText->setScale({ 1.0f, 2.0f });
		_scoreDisplay->setScale({ 1.0f, 2.0f });
		_levelText->setScale({ 1.0f, 2.0f });
		_levelDisplay->setScale({ 1.0f, 2.0f });
		_goalText->setScale({ 1.0f, 2.0f });
		_goalDisplay->setScale({ 1.0f, 2.0f });

		_scorerg->setPosition({ 50, 50 });
		_scoreDisplay->setPositionX(_scoreText->getLocalBounds().width);

		_currentLevelDisplay->setPositionX(_currentLevelText->getLocalBounds().width);

		_levelrg->setPosition({ 1250, 50 });
		_goalText->setPositionY(200);

		_currentLevelText->setPositionY(200);
		_currentLevelDisplay->setPositionY(200);


		auto _gameBoundingBox = _gameText->getLocalBounds();
		auto _overBoundingBox = _overText->getLocalBounds();
		auto sceneCenter = getCenterCoordinates();
		_gameText->setPosition({ sceneCenter.x - (_gameBoundingBox.width / 2.0f), sceneCenter.y - _gameBoundingBox.height });
		_overText->setPosition({ sceneCenter.x - (_overBoundingBox.width / 2.0f), sceneCenter.y });

		_pauseText->setPositionWithAlignment(vector2df{ 1000.0f, 1000.0f }, NodeText::Alignment::Center);

	}

	void GameScene::onDeinit()
	{
		// Remove instances from all nodes.
		clear();
		Scene::onDeinit();
	}

	void GameScene::onEnterScene()
	{
		Scene::onEnterScene();
		p_boardModel = lib::msptr<lib::board::BoardModel>(_gameData.size, this);
		tilesCreated();
		addPlayer();
		_gameData._gameMode = static_cast<GameData::GameModes>(_gameConfig.value(GameModeStr)->get<int>());

		_score = 0;
		_nextTokenPart = 0;
		setLevel(_gameConfig.value(StartLevelStr)->get<int>());
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
		_goalDisplay->setPosition(lib::vector2df{ _goalText->getLocalBounds().width, 200 });
		registerEvents();

		setState(Playing);

		gameClock.restart();
	}

	void GameScene::onExitScene()
	{
		_mainBoardrg->clear();
		p_boardModel = nullptr;
		p_player = nullptr;
		_backgroundTilesrg = nullptr;
		m_backgroundTiles.clear();
		Scene::onExitScene();
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
			//_pauseText->getAsText()->setColor(lib::draw::Color(255, 255, 255, 20));
			addAnimation(lib::draw::anim::ColorAnimation::create(1000, _pauseText, lib::draw::Color(255, 255, 255, 0), lib::draw::Color(255, 255, 255, 255)));
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
		logDebug("Level set: ",_levelProperties.currentLevel());
		logDebug("Millis between tokens: ", _levelProperties.millisBetweenTokens());
		logDebug("Current base score: ", _levelProperties.baseScore());
		logDebug("Seconds to next level: ", _levelProperties.stayTime());
		logDebug("Tokens to next level: ",_levelProperties.stayTokens());

		_gameData.levelClock.restart();
		_gameData.consumedTokens = 0;

		// Update background tiles
		for (lib::u32 y = 0; y < _gameData.size.y; ++y)
		{
			for (lib::u32 x = 0; x < _gameData.size.x; ++x)
			{
				m_backgroundTiles[y][x]->setColor(_levelProperties.getBackgroundTileColor(x, y, pointInCenter(lib::vector2du32{ x,y })));
				
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
		_tokenZones[0].zone = Rectu32{ 0,centerRect.top,centerRect.left - 1, centerRect.bottom() - 1 };
		_tokenZones[0].direction = Direction::DirectionData::Right;

		// From top to bottom
		_tokenZones[1].zone = Rectu32{ centerRect.left , 0, centerRect.right() - 1, centerRect.top - 1 };
		_tokenZones[1].direction = Direction::DirectionData::Down;

		// From right to left
		_tokenZones[2].zone = Rectu32{ size.x - 1 , centerRect.top,  centerRect.right(), centerRect.bottom() - 1 };
		_tokenZones[2].direction = Direction::DirectionData::Left;

		// From bottom to top
		_tokenZones[3].zone = Rectu32{ centerRect.left , size.y, centerRect.right() - 1, centerRect.bottom() - 1 };
		_tokenZones[3].direction = Direction::DirectionData::Up;

		for (u32 i = 0; i < NUMWAYS; ++i) {
			_tokenZones[i].size = _tokenZones[i].direction.isHorizontal() ? centerRect.size().y : centerRect.size().x;
		}
	}

	void GameScene::generateNextToken()
	{
		const GameData::TokenZone &currentTokenZone{ _gameData._tokenZones[_nextTokenPart] };

		logDebug("NextTokenPart: ", std::to_string(_nextTokenPart));
		logDebug("left: ", currentTokenZone.zone.left, " top: ", currentTokenZone.zone.top,
			" size: ", currentTokenZone.zone.size().x, " y2: ", currentTokenZone.zone.size().y);

		u32 newToken = 0;// getRandomNumer(NUMTOKENS);

		u32 sizep = 0;// getRandomNumer(currentTokenZone.size);

		u32 newX = currentTokenZone.zone.left + (currentTokenZone.direction.isHorizontal() ? 0 : sizep);
		lib::u32 newY = currentTokenZone.zone.top + (currentTokenZone.direction.isHorizontal() ? sizep : 0);
		logDebug("New tile pos: ", newX, ",", newY);

		vector2du32 loopPosition{ (currentTokenZone.direction.isHorizontal() ? currentTokenZone.zone.size().x : newX),
			(currentTokenZone.direction.isHorizontal() ? newY : currentTokenZone.zone.size().y) };
//		lib::vector2du32 destPosition;
		logDebug("Starting at: ", loopPosition.x, ",", loopPosition.y);

		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		Direction loopDirection = currentTokenZone.direction.negate();
		for_each_token_in_line(loopPosition, loopDirection, [this](const vector2du32 &loopPosition, const Direction &direction)
		{
			if (!p_boardModel->tileEmpty(loopPosition))
			{
				vector2du32 dest = direction.negate().applyToVector(loopPosition);
				p_boardModel->moveTile(loopPosition, dest);

				if (pointInCenter(dest))
				{
					startGameOver();
				}
			}
			return true;
		});
		// Set the new token
		addNewToken(vector2du32{ newX, newY }, newToken);
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
		do {
			stay &= updatePredicate(loopPosition, direction);
			loopPosition = direction.applyToVector(loopPosition);
			stay &= p_boardModel->validCoords(loopPosition);
		} while (stay);
	}

	void GameScene::addPlayer()
	{
		logDebug("Adding player tile at ", _gameData.centerRect.left, ",", _gameData.centerRect.top);
		__ASSERT(!p_player, "Player already initialized");
		// Create the player instance
		p_player = lib::sptr<Player>(new Player(lib::vector2du32(_gameData.centerRect.leftTop()),tileSize()));

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(p_player->boardPosition(), std::dynamic_pointer_cast<lib::board::ITile>(_mainBoardrg->addRenderizable(p_player)));
	}

	void GameScene::addNewToken(const lib::vector2du32 &position, lib::u32 newToken)
	{
		logDebug("Adding new tile at ", position.x, ",", position.y, " with value ", newToken);
		// Create a new Tile instance
		lib::sptr<Tile> newTileToken = lib::sptr<Tile>(new Tile(lib::board::BoardTileData(newToken),tileSize()));
		// Set the position in the scene depending on the board position
		newTileToken->setPosition(board2Scene(position));

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(position, std::dynamic_pointer_cast<lib::board::ITile>(_mainBoardrg->addRenderizable(newTileToken)));
	}

	void zoper::GameScene::registerEvents()
	{
		addSubscription(events::KeyPressedEvent::subscribe([this](const events::Event&ev) {
			logDebug("Key pressed in GameScene");
			const auto &kEvent{ dynamic_cast<const events::KeyPressedEvent&>(ev) };
			switch (state())
			{
			case Playing:
			{
				auto dir = _keyMapping.getDirectionFromKey(kEvent.key);
				if (dir.isValid()) {
					p_player->setCurrentDirection(dir);
					movePlayer(dir);
				}
				else if (_keyMapping.isLaunchKey(kEvent.key)) {
					launchPlayer();
				}
				else if (_keyMapping.isPauseKey(kEvent.key)) {
					switchPause();
				}
			}
			break;
			case GameOver:
				lib::host().setScene("MenuScene");
				break;
			case Pause:
				if (_keyMapping.isPauseKey(kEvent.key)) {
					switchPause();
				}
				break;
			}
		}));
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

	void GameScene::onAnimationStarted(lib::sptr<lib::draw::anim::IAnimation> anim, lib::sptr<lib::draw::Renderizable> node)
	{
	}

	void GameScene::onAnimationFinished(lib::sptr<lib::draw::anim::IAnimation> anim, lib::sptr<lib::draw::Renderizable> node)
	{
		if (anim->animationType() == "ColorAnimation" && node == _pauseText)
		{
			_pauserg->setVisible(state()==Pause);
			_pauseText->setColor(lib::draw::colors::White);
		}
		else if (anim->animationType() == "PositionAnimation" && node->name() == "pointIncrementScore")
		{
			removeRenderizable(node);
		}
	}

	void GameScene::launchPlayer()
	{
		logDebug("Launching player");
		const Direction loopDirection = p_player->currentDirection();
		lib::vector2du32 loopPosition{ p_player->boardPosition() };
		lib::board::BoardTileData tokenType = p_player->getData();
		lib::u32 inARow{ 0 };
		for_each_token_in_line(loopPosition, loopDirection, [this,tokenType,&inARow](const lib::vector2du32 &loopPosition, const Direction &direction)
		{
			direction;
			bool result{ true };
			bool found{ false };
			lib::vector2df lastTokenPosition;

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
					logDebug("Player type changed to ", p_player->getData());
					result = false;
				}
			}
			if (found)
			{
				auto node = createShape("pointIncrementScore", vector2df{ 15.0f,15.0f },nullptr,30, colors::White);
				addAnimation(anim::PositionAnimation::create(600, node, lastTokenPosition, lib::vector2df(450,100)));
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
			if (position.x < _gameData.centerRect.left || position.y < _gameData.centerRect.top)
				return false;

			if (position.x >= _gameData.centerRect.right() || position.y >= _gameData.centerRect.bottom())
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
			logDebug(temp);
		}
	}

	void GameScene::tilesCreated()
	{
		_backgroundTilesrg = createNewRenderGroup("backgroundTiles", _mainBoardrg);
		for (u32 y = 0; y < _gameData.size.y; ++y)
		{
			std::vector<sptr<NodeQuad>> column;

			for (u32 x = 0; x < _gameData.size.x; ++x)
			{
				auto tileBackground = _backgroundTilesrg->createSpriteShape("backgroundTile", tileSize(),nullptr, colors::White);
				tileBackground->setPosition(board2Scene(vector2du32{ x,y }));
				column.push_back(std::move(tileBackground));

				auto node = _backgroundTilesrg->createShape("backgroundTilePoint", vector2df{ 10.0f,10.0f },nullptr,30, colors::White);
				vector2df center( board2Scene(vector2du32{ x,y }) );
				center.x += tileSize().x / 2.0f;
				center.y += tileSize().y / 2.0f;
				center.x -= (node->getLocalBounds().width / 2.0f);
				center.y -= (node->getLocalBounds().height / 2.0f);
				node->setPosition(center);
				node->setColor(lib::draw::colors::White);
			}
			m_backgroundTiles.push_back(column);
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
		addAnimation(lib::draw::anim::PositionAnimation::create(_levelProperties.millisBetweenTokens() / 2, tile, board2Scene(dest)));
	}

	void GameScene::tokenAppeared(const lib::vector2du32 &position, lib::sptr<Tile> tile)
	{
		position;
		tile;
	}

	void GameScene::tokenDissapeared(const lib::vector2du32 &position, lib::sptr<Tile> tile)
	{
		position;
		logDebug("Deleting token ", tile->name(), " from scene");
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
