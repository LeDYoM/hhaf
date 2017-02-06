#include "gamescene.hpp"

#include "tile.hpp"
#include "player.hpp"
#include "common.hpp"
#include <lib/board/boardmodel.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/core/log.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodequad.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/inputevent.hpp>
#include <lib/include/properties.hpp>
#include <lib/draw/ianimation.hpp>

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

	GameScene::~GameScene() = default;

	void GameScene::onInit()
	{
		Scene::onInit();
		_mainBoardrg = this->createSceneNode("mainBoard");
		_gameOverrg = this->createSceneNode("gameOverScreen");
		_scorerg = this->createSceneNode("score");
		_levelrg = this->createSceneNode("level");
		_pauserg = this->createSceneNode("pause");

		auto& resourceManager{ lib::host().resourceManager() };
		auto scoreFont(resourceManager.getFont("game_scene.scoreFont"));
		_scoreText = _scorerg->createRenderizable<NodeText>("scoretxt", "Score: ", scoreFont, 90, colors::Blue);
		_scoreDisplay = _scorerg->createRenderizable<NodeText>("scoredisplay", "", scoreFont, 90, colors::White);
		_currentLevelText = _scorerg->createRenderizable<NodeText>("currentLevelText", "Level: ", scoreFont, 90, colors::Blue);
		_currentLevelDisplay = _scorerg->createRenderizable<NodeText>("currentLevelDisplay", "0", scoreFont, 90, colors::White);
		_levelText = _levelrg->createRenderizable<NodeText>("leveltxt", "", scoreFont, 90, colors::Blue);
		_levelDisplay = _levelrg->createRenderizable<NodeText>("leveldisplay", "", scoreFont, 90, colors::White);
		_goalText = _levelrg->createRenderizable<NodeText>("goalText", "", scoreFont, 90, colors::Blue);
		_goalDisplay = _levelrg->createRenderizable<NodeText>("goalDisplay", "", scoreFont, 90, colors::White);
		_pauseText = _pauserg->createRenderizable<NodeText>("pausetext", "PAUSE", scoreFont, 180, colors::White);

		_gameText = _gameOverrg->createRenderizable<NodeText>("gameovergame", "GAME", scoreFont, 360, colors::White);
		_overText = _gameOverrg->createRenderizable<NodeText>("gameoverover", "OVER", scoreFont, 360, colors::White);

		increaseScore(0);

		_scoreText->scale = { 1.0f, 2.0f };
		_scoreDisplay->scale = { 1.0f, 2.0f };
		_levelText->scale = { 1.0f, 2.0f };
		_levelDisplay->scale = { 1.0f, 2.0f };
		_goalText->scale = { 1.0f, 2.0f };
		_goalDisplay->scale = { 1.0f, 2.0f };

		_scorerg->position = { 50, 50 };
		_scoreDisplay->position = {_scoreText->bounds().width, _scoreDisplay->position().y};

		_currentLevelDisplay->position = { _currentLevelText->bounds().width,_currentLevelDisplay->position().y };

		_levelrg->position = { 1250, 50 };
		_goalText->position = { _goalText->position().x, 200 };

		_currentLevelText->position = { _currentLevelText->position().x, 200 };
		_currentLevelDisplay->position = { _currentLevelDisplay->position().x, 200 };


		auto _gameBoundingBox = _gameText->bounds();
		auto _overBoundingBox = _overText->bounds();
		auto sceneCenter = getCenterCoordinates();
		_gameText->position = { sceneCenter.x - (_gameBoundingBox.width / 2.0f), sceneCenter.y - _gameBoundingBox.height };
		_overText->position = { sceneCenter.x - (_overBoundingBox.width / 2.0f), sceneCenter.y };

		_pauseText->setAlignmentX(0, 2000, NodeText::Alignment::Center);
		_pauseText->setAlignmentY(0, 2000, NodeText::Alignment::Center);
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
		using namespace lib::board;
		using namespace lib::events;

		p_boardModel = lib::msptr<BoardModel>(_gameData.size);
		m_boardEventConnector.addSubscription(TileAddedEvent::subscribe([this](const events::Event&ev) {
			auto tEvent{ eventAs<TileAddedEvent>(ev) }; tileAdded(tEvent.position, tEvent.tile); 
		}));
		m_boardEventConnector.addSubscription(TileDeletedEvent::subscribe([this](const events::Event&ev) {
			auto tEvent{ eventAs<TileDeletedEvent>(ev) }; tileDeleted(tEvent.position, tEvent.tile);
		}));
		m_boardEventConnector.addSubscription(TileChangedEvent::subscribe([this](const events::Event&ev) {
			auto tEvent{ eventAs<TileChangedEvent>(ev) }; tileChanged(tEvent.position, tEvent.tile, tEvent.ov, tEvent.nv);
		}));
		m_boardEventConnector.addSubscription(TileMovedEvent::subscribe([this](const events::Event&ev) {
			auto tEvent{ eventAs<TileMovedEvent>(ev) }; tileMoved(tEvent.position, tEvent.dest, tEvent.tile);
		}));

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
			_levelText->text = "Tokens: ";
			_goalText->text = "Goal: ";
			break;

		case GameData::GameModes::Time:
			_levelText->text = "Time: ";
			_goalText->text.set("Goal: ");
			break;
		}

		_levelDisplay->position = {_levelText->bounds().width, _levelDisplay->position().y};
		_goalDisplay->position = { _goalText->bounds().width, 200 };
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

	void GameScene::updateScene()
	{
		if (state() == Playing) {
			if (_gameData._gameMode == GameData::GameModes::Time) {
				updateLevelData();
			}

			if (gameClock.getElapsedTime().asMilliSeconds() > static_cast<lib::u64>(_levelProperties.millisBetweenTokens())) {
				// New token
				generateNextToken();
				gameClock.restart();
			}
		} else {
			
		}
	}

	bool GameScene::switchPause()
	{
		if (state() == Playing) {
			setState(Pause);
			_pauserg->setVisible(true);
			addAnimation(msptr<anim::IPropertyAnimation<Color>>(1000, _pauseText->color, Color{ 255, 255, 255, 0 }, Color{ 255, 255, 255, 255 }, 
				anim::animation_action_callback{}, anim::animation_action_callback{}),nullptr);
			gameClock.pause();
			return true;
		} else if (state() == Pause) {
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
				m_backgroundTiles[y][x]->color.set(_levelProperties.getBackgroundTileColor(x, y, pointInCenter(lib::vector2du32{ x,y })));
				
			}
		}

		updateGoals();
		updateLevelData();
	}

	void GameScene::updateGoals()
	{
		_currentLevelDisplay->text = std::to_string(_levelProperties.currentLevel()+1);

		switch (_gameData._gameMode)
		{
		default:
		case GameData::GameModes::Token:
			_goalDisplay->text = std::to_string(_levelProperties.stayTokens());
			break;

		case GameData::GameModes::Time:
			_goalDisplay->text = std::to_string(_levelProperties.stayTime());
			break;
		}
	}

	void GameScene::updateLevelData()
	{
		switch (_gameData._gameMode)
		{
		default:
		case GameData::GameModes::Token:
			_levelDisplay->text = std::to_string(_gameData.consumedTokens);
			if (_gameData.consumedTokens >= _levelProperties.stayTokens())
				setLevel(_levelProperties.currentLevel() + 1);
			break;

		case GameData::GameModes::Time:
			_levelDisplay->text = std::to_string(static_cast<lib::u16>(_gameData.levelClock.getElapsedTime().asSeconds()));
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
		_tokenZones[3].zone = Rectu32{ centerRect.left , size.y - 1, centerRect.right() - 1, centerRect.bottom() - 1 };
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

		u32 newX{ currentTokenZone.zone.left + (currentTokenZone.direction.isHorizontal() ? 0 : sizep) };
		u32 newY{ currentTokenZone.zone.top + (currentTokenZone.direction.isHorizontal() ? sizep : 0) };
		logDebug("New tile pos: ", newX, ",", newY);

		vector2du32 loopPosition{ (currentTokenZone.direction.isHorizontal() ? currentTokenZone.zone.size().x : newX),
			(currentTokenZone.direction.isHorizontal() ? newY : currentTokenZone.zone.size().y) };
		logDebug("Starting at: ", loopPosition);

		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		Direction loopDirection = currentTokenZone.direction.negate();
		for_each_token_in_line(loopPosition, loopDirection, [this](const vector2du32 &loopPosition, const Direction &direction) {
			if (!p_boardModel->tileEmpty(loopPosition)) {
				vector2du32 dest = direction.negate().applyToVector(loopPosition);
				p_boardModel->moveTile(loopPosition, dest);

				if (pointInCenter(dest)) {
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
		p_player = _mainBoardrg->createRenderizable<Player>( vector2du32{ _gameData.centerRect.leftTop() }, tileSize() );

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(p_player->boardPosition(), std::dynamic_pointer_cast<board::ITile>(p_player));
	}

	void GameScene::addNewToken(const vector2du32 &pos, u32 newToken)
	{
		logDebug("Adding new tile at ", pos, " with value ", newToken);
		// Create a new Tile instance
		auto newTileToken = _mainBoardrg->createRenderizable<Tile>(board::BoardTileData(newToken), tileSize());
		// Set the position in the scene depending on the board position
		newTileToken->position = board2Scene(pos);

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(pos, std::dynamic_pointer_cast<board::ITile>(newTileToken));
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

	void GameScene::launchPlayer()
	{
		logDebug("Launching player");
		const Direction loopDirection{ p_player->currentDirection() };
		const vector2du32 loopPosition{ p_player->boardPosition() };
		const board::BoardTileData tokenType{ p_player->get() };
		u32 inARow{ 0 };
		for_each_token_in_line(loopPosition, loopDirection, [this,tokenType,&inARow](const vector2du32 &loopPosition, const Direction &direction)
		{
			direction;
			bool result{ true };
			bool found{ false };
			vector2df lastTokenPosition;

			if (!p_boardModel->tileEmpty(loopPosition) && !pointInCenter(loopPosition) && result) {
				sptr<board::ITile> currentToken{ p_boardModel->getTile(loopPosition) };
				board::BoardTileData currentTokenType = currentToken->get();
				if (currentTokenType == tokenType) {
					++inARow;
					increaseScore(inARow*_levelProperties.baseScore());
					_gameData.consumedTokens++;
					lastTokenPosition = board2Scene(loopPosition);
					p_boardModel->deleteTile(loopPosition);
					found = true;
				} else {
					p_boardModel->changeTileData(p_player->boardPosition(), currentTokenType);
					p_boardModel->changeTileData(loopPosition, tokenType);
					logDebug("Player type changed to ", p_player->get());
					result = false;
				}
			}

			if (found) {
				auto node = createRenderizable<NodeShape>("pointIncrementScore", vector2df{ 15.0f,15.0f },nullptr,30, colors::White);
				addAnimation(msptr<anim::IPropertyAnimation<vector2df>>(600, node->position, lastTokenPosition, vector2df{ 450, 100 }, 
					anim::noAction, anim::animation_action_callback{ [this, node]() { removeRenderizable(node); } }), nullptr);
			}
			return result;
		});

		if (_gameData._gameMode == GameData::GameModes::Token)
			updateLevelData();
	}

	bool GameScene::pointInCenter(const lib::vector2du32 &pos) const
	{
		if (p_boardModel->validCoords(pos))
		{
			if (pos.x < _gameData.centerRect.left || pos.y < _gameData.centerRect.top)
				return false;

			if (pos.x >= _gameData.centerRect.right() || pos.y >= _gameData.centerRect.bottom())
				return false;

			return true;
		}
		return false;
	}

	const lib::vector2df GameScene::board2Scene(const lib::vector2du32 &bPosition) const
	{
		return lib::vector2df{ (getView()->perspective().size().x * bPosition.x) / static_cast<float>(p_boardModel->size().x),
			(getView()->perspective().size().y * bPosition.y) / static_cast<float>(p_boardModel->size().y) };
	}

	const lib::vector2df GameScene::tileSize() const
	{
		return board2Scene(lib::vector2du32( 1, 1 ));
	}

	void GameScene::_debugDisplayBoard() const
	{
		for (u32 y = 0; y < _gameData.size.y; ++y) {
			std::string temp;
			for (u32 x = 0; x < _gameData.size.x; ++x) {
				std::string chTemp;
				auto lp_tile (p_boardModel->getTile(lib::vector2du32(x, y)));
				if (lp_tile) {
					chTemp = std::to_string(lp_tile->get());
				} else {
					chTemp = "*";
					if (pointInCenter(lib::vector2du32(x, y))) {
						chTemp = "C";
					}
				}

				temp += chTemp;
			}
			logDebug(temp);
		}
	}

	void GameScene::tilesCreated()
	{
		_backgroundTilesrg = createSceneNode("backgroundTiles", _mainBoardrg);
		for (u32 y = 0; y < _gameData.size.y; ++y)
		{
			std::vector<sptr<NodeQuad>> column;

			for (u32 x = 0; x < _gameData.size.x; ++x)
			{
				auto tileBackground = _backgroundTilesrg->createRenderizable<NodeQuad>("backgroundTile", tileSize(),nullptr, colors::White);
				tileBackground->position = board2Scene(vector2du32{ x,y });
				column.push_back(std::move(tileBackground));

				auto node = _backgroundTilesrg->createRenderizable<NodeShape>("backgroundTilePoint", vector2df{ 10.0f,10.0f },nullptr,30, colors::White);
				vector2df center( board2Scene(vector2du32{ x,y }) );
				center.x += tileSize().x / 2.0f;
				center.y += tileSize().y / 2.0f;
				center.x -= (node->bounds().width / 2.0f);
				center.y -= (node->bounds().height / 2.0f);
				node->position = center;
			}
			m_backgroundTiles.push_back(column);
		}
	}

	void GameScene::tileAdded(const lib::vector2du32 &pos, board::SITilePointer nTile)
	{
		// Tile appeared
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile))
		{
			tokenAppeared(pos, ztile);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile))
		{
			// Set the position in the scene depending on the board position
			playerAppeared(pos, ztile_);
		}
	}

	void GameScene::tileDeleted(const lib::vector2du32 &pos, lib::board::SITilePointer nTile)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile)) {
			tokenDissapeared(pos,ztile);
		} else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile)) {
			playerDissapeared(pos,ztile_);
		}
	}

	void GameScene::tileMoved(const vector2du32 &source, const lib::vector2du32 &dest, board::SITilePointer tile)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(tile)) {
			tokenMoved(source, dest, ztile);
		} else if (auto ztile_ = std::dynamic_pointer_cast<Player>(tile)) {
			playerMoved(source, dest, ztile_);
		}
	}

	void GameScene::tileChanged(const lib::vector2du32 &pos, lib::board::SITilePointer nTile, 
		const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile)) {
			tokenChangedValue(pos, ztile, ov, nv);
		} else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile)) {
			playerChangedValue(pos, ztile_, ov, nv);
		}
	}

	void GameScene::tokenMoved(const lib::vector2du32 &, const lib::vector2du32 &dest, lib::sptr<Tile> tile)
	{
		addAnimation(msptr<draw::anim::IPropertyAnimation<vector2df>>
			(_levelProperties.millisBetweenTokens() / 2, tile->position, tile->position(), board2Scene(dest),
			anim::noAction, anim::noAction),nullptr);
	}

	void GameScene::tokenAppeared(const lib::vector2du32 &_position, lib::sptr<Tile> tile)
	{
		_position;
		tile;
		logDebug("Token ", tile->name(), " appeared at ", _position);
	}

	void GameScene::tokenDissapeared(const lib::vector2du32 &_position, lib::sptr<Tile> tile)
	{
		_position;
		logDebug("Deleting token ", tile->name(), " from scene at position ", _position);
		_mainBoardrg->removeRenderizable(tile);
	}

	void GameScene::tokenChangedValue(const lib::vector2du32 &, lib::sptr<Tile> tile,
		const lib::board::BoardTileData &, const lib::board::BoardTileData &)
	{
		tile->color.set(tile->getColorForToken());
	}

	void GameScene::updatePlayer(const lib::vector2du32 &dest, lib::sptr<Player> player_)
	{
		const auto ts(tileSize());
		const auto tileCenter(ts / 2.0f);
//		player_->origin = tileCenter;
		player_->position = board2Scene(dest) + tileCenter;
		player_->rotation = player_->currentDirection().angle();
		if (player_->currentDirection().value() == Direction::DirectionData::Up ||
			player_->currentDirection().value() == Direction::DirectionData::Down) {
			player_->scale = { 1, 1 };
		}
		else {
			player_->scale = { ts.y / ts.x, ts.x / ts.y };
		}
	}

	void GameScene::playerMoved(const lib::vector2du32 &, const lib::vector2du32 &dest, lib::sptr<Player> player_)
	{
		updatePlayer(dest, player_);
	}

	void GameScene::playerAppeared(const vector2du32 &pos, lib::sptr<Player> player)
	{
		player->position = board2Scene(pos);
	}

	void GameScene::playerDissapeared(const lib::vector2du32 &, lib::sptr<Player> player)
	{
	}

	void GameScene::playerChangedValue(const vector2du32 &, sptr<Player> player,
		const board::BoardTileData &, const board::BoardTileData &)
	{
		player->color.set(player->getColorForToken());
	}

	void GameScene::increaseScore(u32 scoreIncrement)
	{
		_score += scoreIncrement;
		std::string result{ std::to_string(_score) };
		while (result.size() < _scoreSize) result = "0" + result;
		_scoreDisplay->text = result;
	}

	vector2df GameScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}
}
