#include "gamescene.hpp"

#include "tile.hpp"
#include "player.hpp"
#include "constants.hpp"

#include "../common.hpp"
#include "../gameshareddata.hpp"
#include "../zoperprogramcontroller.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <lib/board/boardmodel.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/include/core/log.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/randomizer.hpp>
#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/core/host.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>
#include <lib/scene/components/inputcomponent.hpp>
#include <lib/scene/components/alignedtextcomponent.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;
    using namespace lib::scene::nodes;

    constexpr u32 NumTokens = 5;
    constexpr u32 PlayerToken = NumTokens;

    GameScene::GameScene() : Scene("GameScene") {}

    GameScene::~GameScene() = default;

    void GameSceneData::createData(SceneNode& sceneNode)
    {
        m_mainBoardrg = sceneNode.createSceneNode("mainBoard");
        m_gameOverrg = sceneNode.createSceneNode("gameOverScreen");
        m_levelrg = sceneNode.createSceneNode("level");
        m_pauseSceneNode = sceneNode.createSceneNode("pause");

        m_scoreQuad = sceneNode.createSceneNode<TextQuad>("score", m_gameresources.scoreFont->font(90), colors::White, vector2df{600, 300});
        m_scoreQuad->position.set(vector2df{ 50, 50 });
        m_scoreQuad->text(vector2dst{0,0})->text.set(Text_t("Level:"));
        m_scoreQuad->text(vector2dst{0,0})->textColor = FillColor_t(colors::Blue);
        m_scoreQuad->text(vector2dst{0,1})->text.set(Text_t("Score:"));
        m_scoreQuad->text(vector2dst{0,1})->textColor = FillColor_t(colors::Blue);

        m_goalQuad = sceneNode.createSceneNode<TextQuad>("goal", m_gameresources.scoreFont->font(90), colors::White, vector2df{600, 300});
        m_goalQuad->position.set(vector2df{ 1250, 50 });
        m_goalQuad->text(vector2dst{0,0})->textColor = FillColor_t(colors::Blue);
        m_goalQuad->text(vector2dst{0,1})->textColor = FillColor_t(colors::Blue);

        m_pauseText = m_pauseSceneNode->createSceneNode<SceneNodeText>("pausetext");
        m_pauseText->text.set(Text_t("PAUSE"));
        m_pauseText->font.set(m_gameresources.scoreFont->font(180));
        m_pauseText->textColor.set(FillColor_t{colors::White});
        {
            auto align(m_pauseText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(sceneNode.scenePerspective().size());
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Middle);
        }

        vector2df gosize{ sceneNode.scenePerspective().width, 715 };
        m_gameOverrg->position.set({0, 575});

        auto gameText(m_gameOverrg->createSceneNode<SceneNodeText>("gameovergame"));
        gameText->text.set(Text_t("GAME"));
        gameText->font.set(m_gameresources.scoreFont->font(360));
        gameText->textColor.set(FillColor_t{colors::White});
        {
            auto align(gameText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(gosize);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Top);
        }

        auto overText(m_gameOverrg->createSceneNode<SceneNodeText>("gameoverover"));
        overText->text.set(Text_t("OVER"));
        overText->font.set(m_gameresources.scoreFont->font(360));
        overText->textColor.set(FillColor_t{colors::White});
        {
            auto align(overText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(gosize);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Bottom);
        }

        m_levelrg->position = vector2df{ 1250, 50 };

        m_gameOverrg->visible = false;
        m_mainBoardrg->visible = true;
        m_pauseSceneNode->visible = false;
    }

    void GameScene::onCreated()
    {
        BaseClass::onCreated();

        m_data = msptr<GameSceneData>();
        m_data->createData(*this);

        m_gameresources.loadResources(host().resourceManager());

        increaseScore(0);

        using namespace lib::board;

        m_tokenZones.generateTokenZones();

        p_boardModel = this->ensureComponentOfType<BoardModelComponent>();
        p_boardModel->initialize(m_tokenZones.size);

        p_boardModel->TileAdded.connect([this](const vector2dst position_, SITilePointer tile) {
			// Tile appeared
			if (auto ztile = std::dynamic_pointer_cast<Tile>(tile)) {
				lib::log_debug_info("Token ", ztile->name(), " appeared at ", position_);
			}
			else if (auto player = std::dynamic_pointer_cast<Player>(tile)) {
				// Set the position in the scene depending on the board position
				player->boardPosition = position_;
			}
        });

        p_boardModel->TileRemoved.connect([this](const vector2dst position_, SITilePointer tile) {
			if (auto ztile = std::dynamic_pointer_cast<Tile>(tile)) {
				lib::log_debug_info("Deleting token ", ztile->name(), " from scene at position ", position_);
                m_data->m_mainBoardrg->removeSceneNode(ztile);
			} /*else if (auto ztile_ = std::dynamic_pointer_cast<Player>(tile)) {
			  // Actually, never used
			  }*/
		});

        p_boardModel->TileChanged.connect([this](const vector2dst position_, SITilePointer tile,
                                          const BoardTileData oldValue, const BoardTileData newValue) {
			if (auto ztile = std::dynamic_pointer_cast<Tile>(tile)) {
				lib::log_debug_info("Token at position ", position_, " changed from ", oldValue, " to ", newValue);
				ztile->set(newValue);
			}
			else if (auto ztile_ = std::dynamic_pointer_cast<Player>(tile)) {
				lib::log_debug_info("Player (position ", position_, ") changed from ", oldValue, " to ", newValue);
				ztile_->set(newValue);
			}
		});

        p_boardModel->TileMoved.connect([this](const vector2dst source, const vector2dst dest, SITilePointer tile) {
			if (auto ztile = std::dynamic_pointer_cast<Tile>(tile)) {
				tokenMoved(source, dest, ztile);
			}
			else if (auto ztile_ = std::dynamic_pointer_cast<Player>(tile)) {
				ztile_->updateDirection();
			}
		});

        tilesCreated();
        addPlayer();

        m_nextTokenPart = 0;
        importGameSharedData();
        m_score = 0;

        switch (m_gameMode)
        {
        default:
        case GameMode::Token:
            m_goalQuad->text(vector2dst{0,0})->text.set(Text_t("Tokens: "));
            m_goalQuad->text(vector2dst{0,1})->text.set(Text_t("Goal: "));
            break;

        case GameMode::Time:
            m_goalQuad->text(vector2dst{0,0})->text.set(Text_t("Time: "));
            m_goalQuad->text(vector2dst{0,1})->text.set(Text_t("Goal: "));
            break;
        }

        auto inputComponent(ensureComponentOfType<scene::InputComponent>());
        inputComponent->KeyPressed.connect([this](const lib::input::Key&key) {
            log_debug_info("Key pressed in GameScene");
            const auto &keyMapping = host().app<ZoperProgramController>().keyMapping;
            switch (state())
            {
            case Playing:
            {
                auto dir(keyMapping->getDirectionFromKey(key));
                if (dir.isValid()) {
                    m_player->movePlayer(dir, [this](const vector2dst&p) { return pointInCenter(p); }, p_boardModel);
                }
                else if (keyMapping->isLaunchKey(key)) {
                    launchPlayer();
                }
                else if (keyMapping->isPauseKey(key)) {
					setState(Pause);
				}
            }
            break;
            case GameOver:
                sceneManager().terminateScene();
                break;
            case Pause:
                if (keyMapping->isPauseKey(key)) {
					setState(Playing);
				}
                break;
            }
        });

        m_sceneTimerComponent = ensureComponentOfType<scene::TimerComponent>();

        m_nextTokenTimer = m_sceneTimerComponent->addTimer(
            TimerType::Continuous,
            TimeFromMillis(levelProperties.millisBetweenTokens()),
            [this](Time realEllapsed) {
                log_debug_info("Elapsed between tokens: ", realEllapsed.asMilliSeconds());
                // New token
                generateNextToken();
            }
        );

        m_updateLevelDataTimer = m_sceneTimerComponent->addTimer(
            TimerType::Continuous,
            TimeFromMillis(120),
            [this](Time realEllapsed) {
                updateLevelData();
            }
        );

        StatesControllerActuatorRegister<size_type> gameSceneActuatorRegister;
        gameSceneActuatorRegister.registerStatesControllerActuator(*m_sceneStates, *this);
        setState(Playing);
        clock.restart();
    }

    void GameScene::updateScene()
    {
    }

	void GameScene::onEnterState(const size_type &state)
	{
		switch (state) {
		case Pause:
		{
            m_sceneTimerComponent->pause();
			m_pauseSceneNode->visible = true;
			auto animationComponent(m_pauseSceneNode->ensureComponentOfType<anim::AnimationComponent>());
            animationComponent->addAnimation(muptr<anim::IPropertyAnimation<FillColor_t>>(
                TimeFromMillis(1000), 
                m_pauseText->textColor, FillColor_t{Color{ 255, 255, 255, 0 } },
                                 FillColor_t{Color{ 255, 255, 255, 255 } }));
		}
		break;
        case GameOver:
            m_gameOverrg->visible = true;
            break;
		default:
			break;
		}
        log_debug_info("Entered state: ", state);
    }

    void GameScene::onExitState(const size_type &state)
    {
		switch (state) {
		case Pause:
		{
            m_sceneTimerComponent->resume();
			m_pauseSceneNode->visible = false;
		}
		break;
		default:
			break;
		}
		log_debug_info("Exited state: ", state);
    }

    void GameScene::setLevel(const u32 nv)
    {
        levelProperties.setLevel(nv);
        log_debug_info("Level set: ", levelProperties.currentLevel());
        log_debug_info("Millis between tokens: ", levelProperties.millisBetweenTokens());
        log_debug_info("Current base score: ", levelProperties.baseScore());
        log_debug_info("Seconds to next level: ", levelProperties.stayTime());
        log_debug_info("Tokens to next level: ", levelProperties.stayTokens());

        m_levelTimer.restart();
        m_consumedTokens = 0;

        // Update background tiles
        m_boardGroup->for_each_tableSceneNode([this](const auto position, auto node) {
            node->setTileColor(levelProperties.getBackgroundTileColor(position, pointInCenter(position)));
        });

        updateGoals();
        updateLevelData();
    }

    void GameScene::updateGoals()
    {
        m_scoreQuad->text(vector2dst{1,0})->text.set(Text_t(make_str(levelProperties.currentLevel() + 1)));

        switch (m_gameMode)
        {
        default:
        case GameMode::Token:
            m_goalQuad->text(vector2dst{1,1})->text.set(Text_t(make_str(levelProperties.stayTokens())));
            break;

        case GameMode::Time:
            m_goalQuad->text(vector2dst{1,1})->text.set(Text_t(make_str(levelProperties.stayTime())));
            break;
        }
    }

    void GameScene::updateLevelData()
    {
        switch (m_gameMode)
        {
        default:
        case GameMode::Token:
            m_goalQuad->text(vector2dst{1,0})->text.set(Text_t(m_consumedTokens));
            if (m_consumedTokens >= levelProperties.stayTokens())
                setLevel(levelProperties.currentLevel() + 1);
            break;

        case GameMode::Time:
            m_goalQuad->text(vector2dst{1,0})->text.set(
                        Text_t(static_cast<u16>(
                                   m_levelTimer.getElapsedTime().asSeconds())));
            if (m_levelTimer.getElapsedTime().asSeconds() >= levelProperties.stayTime())
                setLevel(levelProperties.currentLevel() + 1);
            break;
        }
    }

    void GameScene::generateNextToken()
    {
        const TokenZones::TokenZone &currentTokenZone{ m_tokenZones.tokenZones[m_nextTokenPart] };

        log_debug_info("NextTokenPart: ", m_nextTokenPart);
        log_debug_info("zone: ", currentTokenZone.zone);

        // Generate the new token type
        const size_type newToken{ randomizer().getUInt(NumTokens) };

        // Calculate in wich tile zone offset is going to appear
        const size_type sizep{ randomizer().getUInt(currentTokenZone.size) };

        // Prepare the position for the new token
        const size_type newX{ currentTokenZone.zone.left + (currentTokenZone.direction.isHorizontal() ? 0 : sizep) };
        const size_type newY{ currentTokenZone.zone.top + (currentTokenZone.direction.isHorizontal() ? sizep : 0) };
        lib::log_debug_info("New tile pos: ", newX, ",", newY);

        vector2dst loopPosition{ (currentTokenZone.direction.isHorizontal() ? currentTokenZone.zone.size().x : newX),
            (currentTokenZone.direction.isHorizontal() ? newY : currentTokenZone.zone.size().y) };
        lib::log_debug_info("Starting at: ", loopPosition);

        // Now, we have the data for the new token generated, but first, lets start to move the row or col.
        Direction loopDirection = currentTokenZone.direction.negate();
        for_each_token_in_line(loopPosition, loopDirection, [this](const vector2dst &loopPosition, const Direction &direction) {
            if (!p_boardModel->tileEmpty(loopPosition)) {
                const auto dest( direction.negate().applyToVector(loopPosition) );
                p_boardModel->moveTile(loopPosition, dest);

                if (pointInCenter(dest)) {
                    log_debug_info("Found point in center: ", dest);
                    // Collided with the center. Game over
                    setState(GameOver);
                }
            }
            return true;
        });
        // Set the new token
        addNewToken(vector2dst{ newX, newY }, newToken);
        m_nextTokenPart = (m_nextTokenPart + 1) % NumWays;

        CLIENT_EXECUTE_IN_DEBUG(_debugDisplayBoard());
    }

    void GameScene::importGameSharedData()
    {
        auto gameSharedData(host().app<ZoperProgramController>().gameSharedData);
        m_gameMode = gameSharedData->gameMode;
        setLevel(gameSharedData->startLevel);

    }

    void GameScene::exportGameSharedData()
    {
    }

    void GameScene::for_each_token_in_line(const vector2dst &startPosition, const Direction &direction,
        function<bool(const vector2dst &, const Direction &)> updatePredicate)
    {
        vector2dst loopPosition{ startPosition };
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
        log_debug_info("Adding player tile at ", m_tokenZones.centerRect);
        CLIENT_ASSERT(!m_player, "Player already initialized");
        // Create the player instance
        m_player = m_mainBoardrg->createSceneNode<Player>("playerNode", m_tokenZones.centerRect.leftTop(), rectFromSize(tileSize()), board2SceneFactor());

        // Add it to the board and to the scene nodes
        p_boardModel->setTile(m_player->boardPosition(), m_player);
    }

    void GameScene::addNewToken(const vector2dst &pos, u32 newToken)
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

    void GameScene::launchPlayer()
    {
        lib::log_debug_info("Launching player");
        const Direction loopDirection{ m_player->currentDirection() };
        const vector2dst loopPosition{ m_player->boardPosition() };
        const board::BoardTileData tokenType{ m_player->get() };
        u32 inARow{ 0 };
        for_each_token_in_line(loopPosition, loopDirection, [this, tokenType, &inARow](const vector2dst &loopPosition, const Direction &)
        {
            bool result{ true };
            bool found{ false };
            vector2df lastTokenPosition;

            if (!p_boardModel->tileEmpty(loopPosition) && !pointInCenter(loopPosition) && result) {
                sptr<board::ITile> currentToken{ p_boardModel->getTile(loopPosition) };
                board::BoardTileData currentTokenType = currentToken->get();
                if (currentTokenType == tokenType) {
                    ++inARow;
                    increaseScore(inARow*levelProperties.baseScore());
                    ++m_consumedTokens;
                    lastTokenPosition = board2Scene(loopPosition);
                    p_boardModel->deleteTile(loopPosition);
                    found = true;
                }
                else {
                    p_boardModel->changeTileData(m_player->boardPosition(), currentTokenType);
                    p_boardModel->changeTileData(loopPosition, tokenType);
                    log_debug_info("Player type changed to ", m_player->get());
                    result = false;
                }
            }

            if (found) {
                auto sceneNode(createSceneNode("pointIncrementScore_SceneNode"));
                auto node(sceneNode->createRenderizable<NodeShape>("pointIncrementScore", 30));
                node->box = rectFromSize(15.0f, 15.0f);
                node->color = colors::White;

                auto animationComponent(sceneNode->ensureComponentOfType<anim::AnimationComponent>());
                animationComponent->
                    addAnimation(muptr<anim::IPropertyAnimation<vector2df>>(
                        TimeFromMillis(gameplay::constants::MillisAnimationPointsToScore),
                        sceneNode->position,
                        lastTokenPosition, gameplay::constants::EndPositionPointsToScore));
                m_sceneTimerComponent->addTimer(TimerType::OneShot, 
                    TimeFromMillis(gameplay::constants::MillisAnimationPointsToScore),
                    [this, sceneNode](auto) { removeSceneNode(sceneNode); } );

                m_player->launchAnimation(lastTokenPosition);
            }
            return result;
        });

        if (m_gameMode == GameMode::Token)
            updateLevelData();
    }

    bool GameScene::pointInCenter(const vector2dst &pos) const
    {
        if (p_boardModel->validCoords(pos)) {
            if (pos.x < m_tokenZones.centerRect.left || pos.y < m_tokenZones.centerRect.top)
                return false;

            if (pos.x >= m_tokenZones.centerRect.right() || pos.y >= m_tokenZones.centerRect.bottom())
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

    vector2df GameScene::board2Scene(const lib::vector2dst &bPosition) const
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
        for (u32 y{ 0 }; y < m_tokenZones.size.y; ++y) {
            str temp;
            for (u32 x{ 0 }; x < m_tokenZones.size.x; ++x) {
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
            log_debug_info(temp);
        }
    }

    void GameScene::tilesCreated()
    {
		assert_debug(!m_boardGroup, "m_boardGroup is not empty");
		m_boardGroup = createSceneNode<BoardGroup>("BoardGroup", m_tokenZones.size);

        moveLastBeforeNode(m_mainBoardrg);
    }

    void GameScene::tokenMoved(const vector2dst &, const vector2dst &dest, sptr<Tile> tile)
    {
        auto animationComponent(tile->ensureComponentOfType<anim::AnimationComponent>());
        animationComponent->addAnimation(muptr<anim::IPropertyAnimation<vector2df>>
            (TimeFromMillis(levelProperties.millisBetweenTokens() / 2), 
                tile->position, tile->position(), board2Scene(dest)));
    }

    constexpr u8 scoreSize = 5;

    void GameScene::increaseScore(u32 scoreIncrement)
    {
        m_score += scoreIncrement;
        str result(m_score);
        while (result.size() < scoreSize) result = "0" + result;
        m_scoreQuad->text(vector2dst{1,1})->text.set(Text_t(result));
    }
}
