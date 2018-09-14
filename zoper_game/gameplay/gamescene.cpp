#include "gamescene.hpp"
#include "gamescenedata.hpp"

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


    void GameScene::onCreated()
    {
        BaseClass::onCreated();

        m_data = msptr<GameSceneData>();
        m_data->createData(*this, m_inGameData.gameMode);

        increaseScore(0);

        using namespace lib::board;

        assert_debug(!m_data->m_boardGroup, "m_boardGroup is not empty");
        m_data->m_boardGroup = createSceneNode<BoardGroup>("BoardGroup", m_tokenZones.size);

        m_data->m_boardGroup->p_boardModel->TileAdded.connect([this](const vector2dst position_, SITilePointer tile) {
			// Tile appeared
            tile->tileAdded(position_);
        });

        m_data->m_boardGroup->p_boardModel->TileRemoved.connect([this](const vector2dst position_, SITilePointer tile) {
			if (auto ztile = std::dynamic_pointer_cast<Tile>(tile)) {
				lib::log_debug_info("Deleting token ", ztile->name(), " from scene at position ", position_);
                m_data->m_boardGroup->m_mainBoardrg->removeSceneNode(ztile);
			} /*else if (auto ztile_ = std::dynamic_pointer_cast<Player>(tile)) {
			  // Actually, never used
			  }*/
		});

        m_data->m_boardGroup->p_boardModel->TileChanged.connect([this](const vector2dst position_, SITilePointer tile,
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

        m_data->m_boardGroup->p_boardModel->TileMoved.connect([this](const vector2dst source, const vector2dst dest, SITilePointer tile) {
			if (auto ztile = std::dynamic_pointer_cast<Tile>(tile)) {
				tokenMoved(source, dest, ztile);
			}
			else if (auto ztile_ = std::dynamic_pointer_cast<Player>(tile)) {
				ztile_->updateDirection();
			}
		});

        addPlayer();

        m_nextTokenPart = 0;

        auto inputComponent(ensureComponentOfType<scene::InputComponent>());
        inputComponent->KeyPressed.connect([this](const lib::input::Key&key) {
            log_debug_info("Key pressed in GameScene");
            const auto &keyMapping = sceneManager().host().app<ZoperProgramController>().keyMapping;
            switch (state())
            {
            case Playing:
            {
                auto dir(keyMapping->getDirectionFromKey(key));
                if (dir.isValid()) {
                    m_player->movePlayer(dir, [this](const vector2dst&p) { return pointInCenter(p); }, m_data->m_boardGroup->p_boardModel);
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

        // Create the general timer component for the scene.
        m_sceneTimerComponent = ensureComponentOfType<scene::TimerComponent>();

        // At this point, we setup level properties.
        // levelProperties should not be used before this point.
        levelProperties.setUp(m_inGameData.currentLevel, m_inGameData.gameMode, m_data, m_sceneTimerComponent);

        m_nextTokenTimer = m_sceneTimerComponent->addTimer(
            TimerType::Continuous,
            TimeFromMillis(levelProperties.millisBetweenTokens()),
            [this](Time realEllapsed) {
            log_debug_info("Elapsed between tokens: ", realEllapsed.asMilliSeconds());
            // New token
            generateNextToken();
        });

        // Import game shared data. Basically, the menu selected options.
        importGameSharedData();

        // Set state controll.
        {
            StatesControllerActuatorRegister<size_type> gameSceneActuatorRegister;
            gameSceneActuatorRegister.registerStatesControllerActuator(*m_sceneStates, *this);
        }
        setState(Playing);
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
            m_data->m_pauseSceneNode->visible = true;
            auto animationComponent(m_data->m_pauseSceneNode->ensureComponentOfType<anim::AnimationComponent>());
            animationComponent->addAnimation(muptr<anim::IPropertyAnimation<FillColor_t>>(
                TimeFromMillis(1000), 
                m_data->m_pauseText->textColor, FillColor_t{Color{ 255, 255, 255, 0 } },
                                 FillColor_t{Color{ 255, 255, 255, 255 } }));
		}
		break;
        case GameOver:
            m_data->m_gameOverrg->visible = true;
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
            m_data->m_pauseSceneNode->visible = false;
		}
		break;
		default:
			break;
		}
		log_debug_info("Exited state: ", state);
    }

    void GameScene::setLevel(const size_type nv)
    {
        levelProperties.setLevel(m_inGameData.currentLevel);

        // Update background tiles
        m_data->m_boardGroup->for_each_tableSceneNode([this](const auto position, auto node) {
            node->setTileColor(levelProperties.getBackgroundTileColor(position, pointInCenter(position)));
        });
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
        for_each_token_in_line(loopPosition, loopDirection, [this](const vector2dst &loopPosition, const Direction &direction) 
        {
            if (!m_data->m_boardGroup->p_boardModel->tileEmpty(loopPosition))
            {
                const auto dest( direction.negate().applyToVector(loopPosition) );
                m_data->m_boardGroup->p_boardModel->moveTile(loopPosition, dest);

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
        (*sceneManager().host().app<ZoperProgramController>().gameSharedData) >> m_inGameData;
        setLevel(m_inGameData.currentLevel);
    }

    void GameScene::exportGameSharedData()
    {
        m_inGameData >> (*sceneManager().host().app<ZoperProgramController>().gameSharedData);
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
            stay &= m_data->m_boardGroup->p_boardModel->validCoords(loopPosition);
        } while (stay);
    }

    void GameScene::addPlayer()
    {
        log_debug_info("Adding player tile at ", m_tokenZones.centerRect);
        CLIENT_ASSERT(!m_player, "Player already initialized");
        // Create the player instance
        m_player = m_data->m_boardGroup->m_mainBoardrg->createSceneNode<Player>("playerNode", m_tokenZones.centerRect.leftTop(), rectFromSize(tileSize()), board2SceneFactor());

        // Add it to the board and to the scene nodes
        m_data->m_boardGroup->p_boardModel->setTile(m_player->boardPosition(), m_player);
    }

    void GameScene::addNewToken(const vector2dst &pos, const size_type newToken)
    {
        using namespace lib::board;

        lib::log_debug_info("Adding new tile at ", pos, " with value ", newToken);
        // Create a new Tile instance
        auto newTileToken = m_data->m_boardGroup->m_mainBoardrg->createSceneNode<Tile>("tileNode", BoardTileData{ static_cast<BoardTileData>(newToken) }, rectFromSize(tileSize()));
        // Set the position in the scene depending on the board position
        newTileToken->position = board2Scene(pos);

        // Add it to the board
        m_data->m_boardGroup->p_boardModel->setTile(pos, newTileToken);
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

            if (!m_data->m_boardGroup->p_boardModel->tileEmpty(loopPosition) && !pointInCenter(loopPosition) && result)
            {
                sptr<board::ITile> currentToken{ m_data->m_boardGroup->p_boardModel->getTile(loopPosition) };
                board::BoardTileData currentTokenType = currentToken->get();

                if (currentTokenType == tokenType) 
                {
                    // If we found a token with the same color than the player:

                    // Increment the number of tokens deleted in a row
                    ++inARow;

                    // Increase the score accordingly
                    increaseScore(inARow * levelProperties.baseScore());

                    // Inform that a token has been consumed
                    levelProperties.tokenConsumed();

                    // Store the position of this last cosumed token
                    lastTokenPosition = board2Scene(loopPosition);

                    // Delete the token
                    m_data->m_boardGroup->p_boardModel->deleteTile(loopPosition);

                    // At least you found one token
                    found = true;
                }
                else 
                {
                    // If we found a token, but it is from another color:

                    // Change the type of the player to this new one
                    m_data->m_boardGroup->p_boardModel->changeTileData(m_player->boardPosition(), currentTokenType);

                    // Change the type of the token for the previous type of the player
                    m_data->m_boardGroup->p_boardModel->changeTileData(loopPosition, tokenType);

                    log_debug_info("Player type changed to ", m_player->get());

                    // Exit the loop
                    result = false;
                }
            }

            if (found) 
            {
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
    }

    bool GameScene::pointInCenter(const vector2dst &pos) const
    {
        if (m_data->m_boardGroup->p_boardModel->validCoords(pos))
        {
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
        return{ sceneManager().viewRect().size().x / static_cast<f32>(m_data->m_boardGroup->p_boardModel->size().x),
            sceneManager().viewRect().size().y / static_cast<f32>(m_data->m_boardGroup->p_boardModel->size().y) };
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
                auto lp_tile(m_data->m_boardGroup->p_boardModel->getTile({ x, y }));
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

    void GameScene::tokenMoved(const vector2dst &, const vector2dst &dest, sptr<Tile> tile)
    {
        auto animationComponent(tile->ensureComponentOfType<anim::AnimationComponent>());
        animationComponent->addAnimation(muptr<anim::IPropertyAnimation<vector2df>>
            (TimeFromMillis(levelProperties.millisBetweenTokens() / 2), 
                tile->position, tile->position(), board2Scene(dest)));
    }

    constexpr u8 scoreSize = 5;

    void GameScene::increaseScore(const size_type scoreIncrement)
    {
        m_inGameData.score += scoreIncrement;
        str result(m_inGameData.score);
        while (result.size() < scoreSize) result = "0" + result;
        m_data->m_scoreQuad->text(vector2dst{1,1})->text.set(Text_t(result));
    }
}
