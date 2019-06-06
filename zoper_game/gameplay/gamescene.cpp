#include "gamescene.hpp"

#include "token.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "gameover.hpp"
#include "gamehud.hpp"
#include "pause.hpp"

#include "../common.hpp"
#include "../gameshareddata.hpp"
#include "../zoperprogramcontroller.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <lib/board/boardmodel.hpp>
#include <logger/include/log.hpp>
#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/core/host.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>
#include <lib/scene/components/inputcomponent.hpp>
#include <lib/scene/components/alignedtextcomponent.hpp>
#include <lib/scene/components/randomizercomponent.hpp>
#include <lib/scene/components/renderizables.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;
    using namespace lib::scene::nodes;

    constexpr u32 NumTokens = 5;
    constexpr u32 PlayerToken = NumTokens;

    struct GameScene::GameScenePrivate
    {
        sptr<RandomizerComponent> token_type_generator_;
        sptr<RandomizerComponent> token_position_generator_;
    };

    void GameScene::onCreated()
    {
        BaseClass::onCreated();

        assert_debug(private_ == nullptr, "Private data pointer is not nullptr!");
        private_ = new GameScenePrivate();

        loadResources(GameResources{});

        m_gameOver = createSceneNode<GameOverSceneNode>("gameOverSceneNode");

        using namespace lib::board;

        assert_debug(!m_boardGroup, "m_boardGroup is not empty");
        m_boardGroup = createSceneNode<BoardGroup>("BoardGroup", TokenZones::size);

        addPlayer();

        m_nextTokenPart = 0;

        auto inputComponent(ensureComponentOfType<scene::InputComponent>());
        inputComponent->KeyPressed.connect([this](const lib::input::Key&key) {
            log_debug_info("Key pressed in GameScene");
            const auto &keyMapping = sceneManager().systemProvider().app<ZoperProgramController>().keyMapping;
            switch (state())
            {
            case Playing:
            {
                auto dir(keyMapping->getDirectionFromKey(key));
                if (dir.isValid()) {
                    m_player->movePlayer(dir, m_boardGroup->p_boardModel);
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
                sceneManager().sceneController()->terminateScene();
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

        // Import game shared data. Basically, the menu selected options.
        importGameSharedData();

        // At this point, we setup level properties.
        // levelProperties should not be used before this point.
        levelProperties = ensureComponentOfType<LevelProperties>();
        levelProperties->levelChanged.connect([this](const auto level)
        {
            // Forward current level where necessary.
            m_boardGroup->setLevel(level);
        });
        levelProperties->setUp(m_inGameData.currentLevel, m_inGameData.gameMode, m_sceneTimerComponent);

        m_nextTokenTimer = m_sceneTimerComponent->addTimer(
            TimerType::Continuous,
            TimePoint_as_miliseconds(levelProperties->millisBetweenTokens()),
            [this](TimePoint realEllapsed) 
            {
                log_debug_info("Elapsed between tokens: ", realEllapsed.milliseconds());
                // New token
                generateNextToken();
            }
        );

        // Set state controll.
        {
            StatesControllerActuatorRegister<size_type> gameSceneActuatorRegister;
            gameSceneActuatorRegister.registerStatesControllerActuator(*m_sceneStates, *this);
        }

        private_->token_type_generator_ = ensureComponentOfType<RandomizerComponent>();
        assert_release(private_->token_type_generator_ != nullptr, "Cannot create RandomizerComponent");
        private_->token_type_generator_->channel.set(1U);
        private_->token_position_generator_ = ensureComponentOfType<RandomizerComponent>();
        assert_release(private_->token_position_generator_ != nullptr, "Cannot create RandomizerComponent");
        private_->token_position_generator_->channel.set(2U);

        // Prepare the pause text.
        pause_node_ = createSceneNode<PauseSceneNode>("PauseNode");

        setState(Playing);
    }

    void GameScene::onFinished()
    {
        if (private_)
        {
            delete private_;
            private_ = nullptr;
        }
        BaseClass::onFinished();
    }

	void GameScene::onEnterState(const size_type &state)
	{
		switch (state) {
		case Pause:
		{
            m_sceneTimerComponent->pause();
            pause_node_->enterPause();
 		}
		break;
        case GameOver:
//            m_data->m_gameOverrg->visible = true;
            break;
		default:
			break;
		}
        log_debug_info("Entered state: ", state);
    }

    void GameScene::onExitState(const size_type &state)
    {
		switch (state) 
        {
            case Pause:
            {
                m_sceneTimerComponent->resume();
                pause_node_->exitPause();
            }
            break;
            default:
                break;
		}
		log_debug_info("Exited state: ", state);
    }

    void GameScene::setLevel(const size_type)
    {
        m_boardGroup->setLevel(m_inGameData.currentLevel);
    }

    void GameScene::generateNextToken()
    {
        const TokenZones::TokenZone &currentTokenZone{ TokenZones::tokenZones[m_nextTokenPart] };

        log_debug_info("NextTokenPart: ", m_nextTokenPart);
        log_debug_info("zone: ", currentTokenZone.zone);

        // Generate the new token type
        const size_type newToken{ private_->token_type_generator_->getUInt(NumTokens) };

        // Calculate in wich tile zone offset is going to appear
        const size_type token_displacement{ private_->token_position_generator_->getUInt(currentTokenZone.size) };

        // Prepare the position for the new token
        const size_type newX{ currentTokenZone.zone.left + (currentTokenZone.direction.isHorizontal() ? 0 : token_displacement) };
        const size_type newY{ currentTokenZone.zone.top + (currentTokenZone.direction.isHorizontal() ? token_displacement : 0) };
        lib::log_debug_info("New tile pos: ", newX, ",", newY);

        vector2dst loopPosition{ (currentTokenZone.direction.isHorizontal() ? currentTokenZone.zone.size().x : newX),
            (currentTokenZone.direction.isHorizontal() ? newY : currentTokenZone.zone.size().y) };
        lib::log_debug_info("Starting at: ", loopPosition);

        // Now, we have the data for the new token generated, but first, lets start to move the row or col.
        Direction loopDirection = currentTokenZone.direction.negate();
        for_each_token_in_line(loopPosition, loopDirection, [this](const vector2dst &loopPosition, const Direction &direction) 
        {
            if (!m_boardGroup->p_boardModel->tileEmpty(loopPosition))
            {
                const auto dest( direction.negate().applyToVector(loopPosition) );
                m_boardGroup->p_boardModel->moveTile(loopPosition, dest);

                if (TokenZones::pointInCenter(dest)) {
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
        (*sceneManager().systemProvider().app<ZoperProgramController>().gameSharedData) >> m_inGameData;
    }

    void GameScene::exportGameSharedData()
    {
        m_inGameData >> (*sceneManager().systemProvider().app<ZoperProgramController>().gameSharedData);
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
            stay &= m_boardGroup->p_boardModel->validCoords(loopPosition);
        } while (stay);
    }

    void GameScene::addPlayer()
    {
        log_debug_info("Adding player tile at ", TokenZones::centerRect.leftTop());
        assert_release(!m_player, "Player already initialized");
        // Create the player instance
        m_player = m_boardGroup->m_mainBoardrg->createSceneNode<Player>("playerNode", TokenZones::centerRect.leftTop(), rectFromSize(tileSize()), board2SceneFactor());

        // Add it to the board and to the scene nodes
        m_boardGroup->p_boardModel->setTile(m_player->boardPosition(), m_player);
    }

    void GameScene::addNewToken(const vector2dst &pos, const size_type newToken)
    {
        using namespace lib::board;

        log_debug_info("Adding new tile at ", pos, " with value ", newToken);
        // Create a new Tile instance
        auto newTileToken = m_boardGroup->m_mainBoardrg->createSceneNode<Token>("tileNode", BoardTileData{ static_cast<BoardTileData>(newToken) }, rectFromSize(tileSize()));
        // Set the position in the scene depending on the board position
        newTileToken->position = board2Scene(pos);

        // Add it to the board
        m_boardGroup->p_boardModel->setTile(pos, newTileToken);
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
            vector2df lastTokenPosition{};

            if (!m_boardGroup->p_boardModel->tileEmpty(loopPosition) && !TokenZones::pointInCenter(loopPosition) && result)
            {
                sptr<board::ITile> currentToken{ m_boardGroup->p_boardModel->getTile(loopPosition) };
                board::BoardTileData currentTokenType = currentToken->get();

                if (currentTokenType == tokenType) 
                {
                    // If we found a token with the same color than the player:

                    // Increment the number of tokens deleted in a row
                    ++inARow;

                    // Increase the score accordingly
                    levelProperties->increaseScore(inARow * levelProperties->baseScore());

                    // Inform that a token has been consumed
                    levelProperties->tokenConsumed();

                    // Store the position of this last cosumed token
                    lastTokenPosition = board2Scene(loopPosition);

                    // Delete the token
                    m_boardGroup->p_boardModel->deleteTile(loopPosition);

                    // At least you found one token
                    found = true;
                }
                else 
                {
                    // If we found a token, but it is from another color:

                    // Change the type of the player to this new one
                    m_boardGroup->p_boardModel->changeTileData(m_player->boardPosition(), currentTokenType);

                    // Change the type of the token for the previous type of the player
                    m_boardGroup->p_boardModel->changeTileData(loopPosition, tokenType);

                    log_debug_info("Player type changed to ", m_player->get());

                    // Exit the loop
                    result = false;
                }
            }

            if (found) 
            {
                auto sceneNode(createSceneNode("pointIncrementScore_SceneNode"));

                auto renderizables_sceneNode = sceneNode->ensureComponentOfType<Renderizables>();
                auto node(renderizables_sceneNode->createNode("pointIncrementScore"));
                node->figType.set(FigType_t::Shape);
                node->pointCount.set(30U);
                node->box = rectFromSize(15.0f, 15.0f);
                node->color = colors::White;

                auto animationComponent(sceneNode->ensureComponentOfType<anim::AnimationComponent>());
                animationComponent->
                    addPropertyAnimation(TimePoint_as_miliseconds(gameplay::constants::MillisAnimationPointsToScore),
                        sceneNode->position,
                        lastTokenPosition, gameplay::constants::EndPositionPointsToScore);
/*                animationComponent->
                    addAnimation(muptr<anim::IPropertyAnimation<vector2df>>(
                        TimePoint_as_miliseconds(gameplay::constants::MillisAnimationPointsToScore),
                        sceneNode->position,
                        lastTokenPosition, gameplay::constants::EndPositionPointsToScore));
*/
                m_sceneTimerComponent->addTimer(TimerType::OneShot, 
                    TimePoint_as_miliseconds(gameplay::constants::MillisAnimationPointsToScore),
                    [this, sceneNode](auto) { removeSceneNode(sceneNode); } );

                m_player->launchAnimation(lastTokenPosition);
            }
            return result;
        });
    }

    vector2df GameScene::board2SceneFactor() const
    {
        return{ sceneManager().viewRect().size().x / static_cast<f32>(m_boardGroup->p_boardModel->size().x),
            sceneManager().viewRect().size().y / static_cast<f32>(m_boardGroup->p_boardModel->size().y) };
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
        for (u32 y{ 0 }; y < TokenZones::size.y; ++y) {
            str temp;
            for (u32 x{ 0 }; x < TokenZones::size.x; ++x) {
                str chTemp;
                auto lp_tile(m_boardGroup->p_boardModel->getTile({ x, y }));
                if (lp_tile) {
                    chTemp = lp_tile->get();
                } else {
                    chTemp = "*";
                    if (TokenZones::pointInCenter({ x, y })) {
                        chTemp = "C";
                    }
                }

                temp += chTemp;
            }
            log_debug_info(temp);
        }
    }
}
