#include "gamescene.hpp"

#include "../tile.hpp"
#include "../player.hpp"
#include "../common.hpp"
#include "../gamedata.hpp"
#include "../zoperprogramcontroller.hpp"
#include <mtypes/include/types.hpp>
#include <lib/board/boardmodel.hpp>
#include <lib/board/itilescontroller.hpp>
#include <mtypes/include/log.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/randomizer.hpp>
#include <lib/scene/renderizable.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/core/host.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>
#include <lib/scene/components/inputcomponent.hpp>


namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;

	constexpr u32 NumTokens = 5;
	constexpr u32 PlayerToken = NumTokens;

	GameScene::GameScene()
		: Scene("GameScene")
	{
	}

	GameScene::~GameScene() = default;

	void GameScene::create()
	{
		BaseClass::create();
		m_gameData = host().app<ZoperProgramController>().gameData;

		m_mainBoardrg = createSceneNode("mainBoard");
		m_gameOverrg = createSceneNode("gameOverScreen");
		m_levelrg = createSceneNode("level");
		m_pauseSceneNode = createSceneNode("pause");

		m_gameresources.loadResources(lib::host().resourceManager());

		m_scoreQuad = createSceneNode<TextQuad>("score", m_gameresources.scoreFont, 90, colors::White, rectFromSize(600, 300));
		m_scoreQuad->position = { 50, 50 };
		m_scoreQuad->text(0)->text = "Level:";
		m_scoreQuad->text(0)->color = colors::Blue;
		m_scoreQuad->text(2)->text = "Score:";
		m_scoreQuad->text(2)->color = colors::Blue;

		m_goalQuad = createSceneNode<TextQuad>("goal", m_gameresources.scoreFont, 90, colors::White, rectFromSize(600, 300));
		m_goalQuad->position = { 1250, 50 };
		m_goalQuad->text(0)->color = colors::Blue;
		m_goalQuad->text(2)->color = colors::Blue;

		vector2df goBoxHalfSize{ 365, 365 };
		Rectf32 gobox{ scenePerspective().center() - goBoxHalfSize, (goBoxHalfSize * 2) };

		m_pauseText = m_pauseSceneNode->createRenderizable<NodeText>("pausetext");
		m_pauseText->text = "PAUSE";
		m_pauseText->font = m_gameresources.scoreFont;
		m_pauseText->characterSize = 180;
		m_pauseText->color = colors::White;
		m_pauseText->alignmentBox = scenePerspective();
		m_pauseText->alignmentX = AlignmentX::Center;
		m_pauseText->alignmentY = AlignmentY::Middle;

		auto gameText(m_gameOverrg->createRenderizable<NodeText>("gameovergame"));
		gameText->text = "GAME";
		gameText->font = m_gameresources.scoreFont;
		gameText->characterSize = 360;
		gameText->color = colors::White;
		gameText->alignmentBox = gobox;
		gameText->alignmentX = AlignmentX::Center;
		gameText->alignmentY = AlignmentY::Top;

		auto overText(m_gameOverrg->createRenderizable<NodeText>("gameoverover"));
		overText->text = "OVER";
		overText->font = m_gameresources.scoreFont;
		overText->color = colors::White;
		overText->alignmentBox = gobox;
		overText->alignmentX = AlignmentX::Center;
		overText->alignmentY = AlignmentY::Bottom;

		increaseScore(0);

		m_levelrg->position = { 1250, 50 };

		using namespace lib::board;
		using namespace lib::events;

		m_gameData->generateTokenZones();

		p_boardModel = this->ensureComponentOfType<BoardModelComponent>();
		p_boardModel->initialize(m_gameData->size);
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

		m_nextTokenPart = 0;
		setLevel(m_gameData->startLevel);
		m_gameData->score = 0;
		m_gameOverrg->visible = false;
		m_mainBoardrg->visible = true;
		m_pauseSceneNode->visible = false;

		switch (m_gameData->gameMode)
		{
		default:
		case GameMode::Token:
			m_goalQuad->text(0)->text = "Tokens: ";
			m_goalQuad->text(2)->text = "Goal: ";
			break;

		case GameMode::Time:
			m_goalQuad->text(0)->text = "Time: ";
			m_goalQuad->text(2)->text = "Goal: ";
			break;
		}

		registerEvents();
		auto inputComponent(ensureComponentOfType<scene::InputComponent>());
		inputComponent->setOnKeyPressedHandler([this](const lib::input::Key&key) {
			log_debug_info("Key pressed in GameScene");
			const auto &keyMapping = host().app<ZoperProgramController>().keyMapping;
			switch (state())
			{
			case Playing:
			{
				auto dir = keyMapping->getDirectionFromKey(key);
				if (dir.isValid()) {
					p_player->movePlayer(dir, [this](const vector2du32&p) { return pointInCenter(p); }, p_boardModel);
				}
				else if (keyMapping->isLaunchKey(key)) {
					launchPlayer();
				}
				else if (keyMapping->isPauseKey(key)) {
					switchPause();
				}
			}
			break;
			case GameOver:
				sceneManager().terminateScene();
				break;
			case Pause:
				if (keyMapping->isPauseKey(key)) {
					switchPause();
				}
				break;
			}
		});

		setState(Playing);

		m_gameClock.restart();
	}

	void GameScene::updateScene()
	{
		if (state() == Playing) {
			if (m_gameData->gameMode == GameMode::Time) {
				updateLevelData();
			}

			if (m_gameClock.getElapsedTime().asMilliSeconds() > static_cast<lib::u64>(levelProperties.millisBetweenTokens())) {
				// New token
				generateNextToken();
				m_gameClock.restart();
			}
		}
		else {
		}
	}

	bool GameScene::switchPause()
	{
		if (state() == Playing) {
			setState(Pause);
			m_pauseSceneNode->visible = true;
			auto animationComponent(m_pauseSceneNode->ensureComponentOfType<anim::AnimationComponent>());
			animationComponent->addAnimation(muptr<anim::IPropertyAnimation<Color>>(1000, m_pauseText->color, Color{ 255, 255, 255, 0 }, Color{ 255, 255, 255, 255 },
				anim::animation_action_callback{}, anim::animation_action_callback{}));
			m_gameClock.pause();
			return true;
		}
		else if (state() == Pause) {
			setState(Playing);
			m_pauseSceneNode->visible = false;
			m_gameClock.resume();
			return false;
		}
		return false;
	}

	void GameScene::setLevel(const u32 nv)
	{
		levelProperties.setLevel(nv);
		lib::log_debug_info("Level set: ", levelProperties.currentLevel());
		lib::log_debug_info("Millis between tokens: ", levelProperties.millisBetweenTokens());
		lib::log_debug_info("Current base score: ", levelProperties.baseScore());
		lib::log_debug_info("Seconds to next level: ", levelProperties.stayTime());
		lib::log_debug_info("Tokens to next level: ", levelProperties.stayTokens());

		m_gameData->levelClock.restart();
		m_gameData->consumedTokens = 0;

		// Update background tiles
		for (u32 y = 0; y < m_gameData->size.y; ++y)
		{
			for (u32 x = 0; x < m_gameData->size.x; ++x)
			{
				m_backgroundTiles[y][x]->color.set(levelProperties.getBackgroundTileColor({ x, y }, pointInCenter({ x,y })));
			}
		}

		updateGoals();
		updateLevelData();
	}

	void GameScene::updateGoals()
	{
		m_scoreQuad->text(1)->text = str(levelProperties.currentLevel() + 1);

		switch (m_gameData->gameMode)
		{
		default:
		case GameMode::Token:
			m_goalQuad->text(3)->text = str(levelProperties.stayTokens());
			break;

		case GameMode::Time:
			m_goalQuad->text(3)->text = str(levelProperties.stayTime());
			break;
		}
	}

	void GameScene::updateLevelData()
	{
		switch (m_gameData->gameMode)
		{
		default:
		case GameMode::Token:
			m_goalQuad->text(1)->text = m_gameData->consumedTokens;
			if (m_gameData->consumedTokens >= levelProperties.stayTokens())
				setLevel(levelProperties.currentLevel() + 1);
			break;

		case GameMode::Time:
			m_goalQuad->text(1)->text = static_cast<lib::u16>(m_gameData->levelClock.getElapsedTime().asSeconds());
			if (m_gameData->levelClock.getElapsedTime().asSeconds() >= levelProperties.stayTime())
				setLevel(levelProperties.currentLevel() + 1);
			break;
		}
	}

	void GameScene::generateNextToken()
	{
		const GameData::TokenZone &currentTokenZone{ m_gameData->tokenZones[m_nextTokenPart] };

		log_debug_info("NextTokenPart: ", m_nextTokenPart);
		log_debug_info("zone: ", currentTokenZone.zone);

		// Generate the new token type
		const u32 newToken{ randomizer().getUInt(NumTokens) };

		// Calculate in wich tile zone offset is going to appear
		const u32 sizep{ randomizer().getUInt(currentTokenZone.size) };

		// Prepare the position for the new token
		const u32 newX{ currentTokenZone.zone.left + (currentTokenZone.direction.isHorizontal() ? 0 : sizep) };
		const u32 newY{ currentTokenZone.zone.top + (currentTokenZone.direction.isHorizontal() ? sizep : 0) };
		lib::log_debug_info("New tile pos: ", newX, ",", newY);

		vector2du32 loopPosition{ (currentTokenZone.direction.isHorizontal() ? currentTokenZone.zone.size().x : newX),
			(currentTokenZone.direction.isHorizontal() ? newY : currentTokenZone.zone.size().y) };
		lib::log_debug_info("Starting at: ", loopPosition);

		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		Direction loopDirection = currentTokenZone.direction.negate();
		for_each_token_in_line(loopPosition, loopDirection, [this](const vector2du32 &loopPosition, const Direction &direction) {
			if (!p_boardModel->tileEmpty(loopPosition)) {
				vector2du32 dest{ direction.negate().applyToVector(loopPosition) };
				p_boardModel->moveTile(loopPosition, dest);

				if (pointInCenter(dest)) {
					log_debug_info("Found point in center: ", dest);
					startGameOver();
				}
			}
			return true;
		});
		// Set the new token
		addNewToken(vector2du32{ newX, newY }, newToken);
		m_nextTokenPart = (m_nextTokenPart + 1) % NumWays;

		CLIENT_EXECUTE_IN_DEBUG(_debugDisplayBoard());
	}

	void GameScene::startGameOver()
	{
		setState(GameOver);
		m_gameOverrg->visible = true;
	}

	void GameScene::for_each_token_in_line(const vector2du32 &startPosition, const Direction &direction,
		function<bool(const vector2du32 &, const Direction &)> updatePredicate)
	{
		vector2du32 loopPosition{ startPosition };
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
		log_debug_info("Adding player tile at ", m_gameData->centerRect);
		CLIENT_ASSERT(!p_player, "Player already initialized");
		// Create the player instance
		p_player = m_mainBoardrg->createSceneNode<Player>("playerNode", m_gameData->centerRect.leftTop(), rectFromSize(tileSize()), board2SceneFactor());

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(p_player->boardPosition(), p_player);
	}

	void GameScene::addNewToken(const vector2du32 &pos, u32 newToken)
	{
		using namespace lib::board;

		lib::log_debug_info("Adding new tile at ", pos, " with value ", newToken);
		// Create a new Tile instance
		auto newTileToken = m_mainBoardrg->createSceneNode<Tile>("tileNode", BoardTileData{ static_cast<BoardTileData>(newToken) }, rectFromSize(tileSize()));
		// Set the position in the scene depending on the board position
		newTileToken->position = board2Scene(pos);

		// Add it to the board
		p_boardModel->setTile(pos, newTileToken);
	}

	void zoper::GameScene::registerEvents()
	{
		/*
		addSubscription(events::KeyPressedEvent::subscribe([this](const events::Event&ev) {
			lib::log_debug_info("Key pressed in GameScene");
			const auto &kEvent{ dynamic_cast<const events::KeyPressedEvent&>(ev) };
			switch (state())
			{
			case Playing:
			{
				auto dir = _keyMapping.getDirectionFromKey(kEvent.key);
				if (dir.isValid()) {
					p_player->movePlayer(dir, [this](const vector2du32&p) { return pointInCenter(p); }, p_boardModel);
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
		*/
	}

	void GameScene::launchPlayer()
	{
		lib::log_debug_info("Launching player");
		const Direction loopDirection{ p_player->currentDirection() };
		const vector2du32 loopPosition{ p_player->boardPosition() };
		const board::BoardTileData tokenType{ p_player->get() };
		u32 inARow{ 0 };
		for_each_token_in_line(loopPosition, loopDirection, [this, tokenType, &inARow](const vector2du32 &loopPosition, const Direction &direction)
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
					increaseScore(inARow*levelProperties.baseScore());
					++(m_gameData->consumedTokens);
					lastTokenPosition = board2Scene(loopPosition);
					p_boardModel->deleteTile(loopPosition);
					found = true;
				}
				else {
					p_boardModel->changeTileData(p_player->boardPosition(), currentTokenType);
					p_boardModel->changeTileData(loopPosition, tokenType);
					lib::log_debug_info("Player type changed to ", p_player->get());
					result = false;
				}
			}

			if (found) {
				auto sceneNode = createSceneNode("pointIncrementScore_SceneNode");
				auto node = sceneNode->createRenderizable<NodeShape>("pointIncrementScore", 30);
				node->box = rectFromSize(15.0f, 15.0f);
				node->color = colors::White;

				auto animationComponent(sceneNode->ensureComponentOfType<anim::AnimationComponent>());
				animationComponent->
					addAnimation(muptr<anim::IPropertyAnimation<vector2df>>(600, sceneNode->position, lastTokenPosition, vector2df{ 450, 100 },
					anim::noAction, anim::animation_action_callback{ [this, sceneNode]() { removeSceneNode(sceneNode); } }));
			}
			return result;
		});

		if (m_gameData->gameMode == GameMode::Token)
			updateLevelData();
	}

	bool GameScene::pointInCenter(const lib::vector2du32 &pos) const
	{
		if (p_boardModel->validCoords(pos)) {
			if (pos.x < m_gameData->centerRect.left || pos.y < m_gameData->centerRect.top)
				return false;

			if (pos.x >= m_gameData->centerRect.right() || pos.y >= m_gameData->centerRect.bottom())
				return false;

			return true;
		}
		return false;
	}

	vector2df GameScene::board2SceneFactor() const
	{
		return{ sceneManager().viewRect().size().x / static_cast<f32>(p_boardModel->size().x),
			sceneManager().viewRect().size().y / static_cast<f32>(p_boardModel->size().y) };
	}

	vector2df GameScene::board2Scene(const lib::vector2du32 &bPosition) const
	{
		const auto b2sf{ board2SceneFactor() };
		return { b2sf.x * bPosition.x, b2sf.y * bPosition.y };
	}

	vector2df GameScene::tileSize() const
	{
		return board2Scene({ 1, 1 });
	}

	void GameScene::_debugDisplayBoard() const
	{
		for (u32 y{ 0 }; y < m_gameData->size.y; ++y) {
			str temp;
			for (u32 x{ 0 }; x < m_gameData->size.x; ++x) {
				str chTemp;
				auto lp_tile(p_boardModel->getTile({ x, y }));
				if (lp_tile) {
					chTemp = lp_tile->get();
				} else {
					chTemp = "*";
					if (pointInCenter({ x, y })) {
						chTemp = "C";
					}
				}

				temp += chTemp;
			}
			lib::log_debug_info(temp);
		}
	}

	void GameScene::tilesCreated()
	{
		const Rectf32 bBox(scenePerspective());
		m_backgroundTiles.clear();
		m_backgroundTiles.reserve(m_gameData->size.y);

		auto backgroundTilesrg(createSceneNode("backgroundTiles"));
		moveLastBeforeNode(m_mainBoardrg);
		f32 currentx{};
		f32 currenty{};
		for (u32 y{ 0 }; y < m_gameData->size.y; ++y) {
			vector<sptr<NodeQuad>> column;
			column.reserve(m_gameData->size.x);

			for (u32 x{ 0 }; x < m_gameData->size.x; ++x) {
				const Rectf32 tileBox{ currentx, currenty, tileSize().x,tileSize().y };
				const str indexStr(x + "_" + y);

				auto tileBackground(backgroundTilesrg->createRenderizable<NodeQuad>("backgroundTile_" + indexStr));
				tileBackground->box = tileBox;
				column.push_back(std::move(tileBackground));

				// Size of the point in the middle of the tile
				constexpr vector2df centerPointSize{ 15,15 };
				constexpr vector2df centerPointSizeHalf{ centerPointSize / 2 };


				auto node(backgroundTilesrg->createRenderizable<NodeShape>("backgroundTilePoint_" + indexStr, 30));
				node->box = { tileBox.center() - (centerPointSize / 2), centerPointSize };
				node->color = colors::White;

				currentx += tileSize().x;
			}
			currentx = 0;
			currenty += tileSize().y;
			m_backgroundTiles.push_back(std::move(column));
		}
	}

	void GameScene::tileAdded(const vector2du32 &pos, board::SITilePointer nTile)
	{
		// Tile appeared
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile)) {
			lib::log_debug_info("Token ", ztile->name(), " appeared at ", pos);
		}
		else if (auto player = std::dynamic_pointer_cast<Player>(nTile)) {
			// Set the position in the scene depending on the board position
			player->boardPosition = pos;
		}
	}

	void GameScene::tileDeleted(const vector2du32 &pos, board::SITilePointer nTile)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile)) {
			lib::log_debug_info("Deleting token ", ztile->name(), " from scene at position ", pos);
			m_mainBoardrg->removeSceneNode(ztile);
		} /*else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile)) {
			// Actually, never used
		}*/
	}

	void GameScene::tileMoved(const vector2du32 &source, const vector2du32 &dest, board::SITilePointer tile)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(tile)) {
			tokenMoved(source, dest, ztile);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(tile)) {
			ztile_->updateDirection();
		}
	}

	void GameScene::tileChanged(const vector2du32 &pos, board::SITilePointer nTile,
		const board::BoardTileData &ov, const board::BoardTileData &nv)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile)) {
			lib::log_debug_info("Token at position ", pos, " changed from ", ov, " to ", nv);
			ztile->set(nv);
		} else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile)) {
			lib::log_debug_info("Player (position ", pos, ") changed from ", ov, " to ", nv);
			ztile_->set(nv);
		}
	}

	void GameScene::tokenMoved(const vector2du32 &, const vector2du32 &dest, sptr<Tile> tile)
	{
		auto animationComponent(tile->ensureComponentOfType<anim::AnimationComponent>());
		animationComponent->addAnimation(muptr<anim::IPropertyAnimation<vector2df>>
			(levelProperties.millisBetweenTokens() / 2, tile->position, tile->position(), board2Scene(dest),
			anim::noAction, anim::noAction));
	}

	constexpr u8 scoreSize = 5;

	void GameScene::increaseScore(u32 scoreIncrement)
	{
		m_gameData->score += scoreIncrement;
		str result(m_gameData->score);
		while (result.size() < scoreSize) result = "0" + result;
		m_scoreQuad->text(3)->text = result;
	}
}