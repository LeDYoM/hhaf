#include "gamescene.hpp"

#include "token.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "gameover.hpp"
#include "gamehud.hpp"
#include "pause.hpp"

#include "../gameshareddata.hpp"
#include "../zoperprogramcontroller.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <lib/board/boardmodel.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>
#include <lib/scene/components/inputcomponent.hpp>
#include <lib/scene/components/alignedtextcomponent.hpp>
#include <lib/scene/components/randomnumberscomponent.hpp>
#include <lib/scene/components/renderizables.hpp>
//TODO: Fixme
#include <lib/system/systemprovider.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;
    using namespace lib::scene::nodes;

    constexpr u32 NumTokens = 5;
    constexpr u32 PlayerToken = NumTokens;

    struct GameScene::GameScenePrivate
    {
        sptr<AnimationComponent> scene_animation_component_;
        sptr<RandomNumbersComponent> token_type_generator_;
        sptr<RandomNumbersComponent> token_position_generator_;
    };

    void GameScene::onCreated()
    {
        BaseClass::onCreated();

        assert_debug(private_ == nullptr, "Private data pointer is not nullptr!");
        private_ = new GameScenePrivate();

        loadResources(GameResources{});

        using namespace lib::board;

        assert_debug(!m_boardGroup, "m_boardGroup is not empty");
        m_boardGroup = createSceneNode<BoardGroup>("BoardGroup", TokenZones::size);

        addPlayer();

        m_nextTokenPart = 0;

        auto inputComponent(addComponentOfType<scene::InputComponent>());
        inputComponent->KeyPressed.connect([this](const lib::input::Key&key) {
            log_debug_info("Key pressed in GameScene");
            // TODO: Fixme
            const auto &keyMapping = sceneManager().systemProvider().app<ZoperProgramController>().keyMapping;
            switch (m_sceneStates->currentState())
            {
            case GameSceneStates::Playing:
            {
                auto dir(keyMapping->getDirectionFromKey(key));
                if (dir.isValid())
                {
                    m_player->movePlayer(dir, m_boardGroup->p_boardModel);
                }
                else if (keyMapping->isLaunchKey(key))
                {
                    launchPlayer();
                }
                else if (keyMapping->isPauseKey(key))
                {
                    m_sceneStates->setState(GameSceneStates::Pause);
                }
            }
            break;
            case GameSceneStates::GameOver:
                sceneManager().sceneController()->terminateScene();
                break;
            case GameSceneStates::Pause:
                if (keyMapping->isPauseKey(key))
                {
                    m_sceneStates->setState(GameSceneStates::Playing);
                }
                break;
            }
        });

        // Create the general timer component for the scene.
        m_sceneTimerComponent = addComponentOfType<scene::TimerComponent>();

        // Import game shared data. Basically, the menu selected options.
        importGameSharedData();

        private_->scene_animation_component_ = addComponentOfType<scene::AnimationComponent>();
        // At this point, we setup level properties.
        // levelProperties should not be used before this point.
        levelProperties = addComponentOfType<LevelProperties>();
        levelProperties->levelChanged.connect([this](const auto level)
        {
            // Forward current level where necessary.
            m_boardGroup->setLevel(level);
        });

        levelProperties->setUp(
            m_inGameData.currentLevel,
            m_inGameData.gameMode,
            m_sceneTimerComponent);

        m_boardGroup->setUp(levelProperties);

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

        m_gameOver = createSceneNode<GameOverSceneNode>("gameOverSceneNode");

        // Set state controll.
        {
            m_sceneStates = addComponentOfType<std::remove_reference_t<decltype(*m_sceneStates)>>();

            StatesControllerActuatorRegister<GameSceneStates> gameSceneActuatorRegister;
            gameSceneActuatorRegister.registerStatesControllerActuator(*m_sceneStates, *this);
        }

        private_->token_type_generator_ = addComponentOfType<RandomNumbersComponent>();
        assert_release(private_->token_type_generator_ != nullptr, "Cannot create DataProviderComponent");
        private_->token_position_generator_ = private_->token_type_generator_; //addComponentOfType<DataProviderComponent>();
        assert_release(private_->token_position_generator_ != nullptr, "Cannot create DataProviderComponent");

        // Prepare the pause text.
        pause_node_ = createSceneNode<PauseSceneNode>("PauseNode");

        m_sceneStates->start(GameSceneStates::Playing);
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

    void GameScene::onEnterState(const GameSceneStates&state)
    {
        switch (state)
        {
        case GameSceneStates::Pause:
        {
            m_sceneTimerComponent->pause();
            pause_node_->enterPause();
        }
        break;
        case GameSceneStates::GameOver:
            m_gameOver->visible = true;
            m_sceneTimerComponent->pause();
            break;
        default:
            break;
        }
        log_debug_info("Entered state: ", static_cast<int>(state));
    }

    void GameScene::onExitState(const GameSceneStates&state)
    {
        switch (state) 
        {
            case GameSceneStates::Pause:
            {
                m_sceneTimerComponent->resume();
                pause_node_->exitPause();
            }
            break;
            default:
                break;
        }
        log_debug_info("Exited state: ", static_cast<int>(state));
    }

    void GameScene::setLevel(const size_type)
    {
        m_boardGroup->setLevel(m_inGameData.currentLevel);
    }

    bool moveTowardsCenter(
        const sptr<board::BoardModelComponent>& p_boardModel,
        const Direction direction,
        const vector2dst position)
    {
        bool moved_to_center{false};

        if (!p_boardModel->tileEmpty(position))
        {
            const auto next = direction.applyToVector(position);

            if (!p_boardModel->tileEmpty(next))
            {
                // If the target position where to move the
                // token is occupied, move the this target first.
                moved_to_center = moveTowardsCenter(p_boardModel, direction, next);
            }
            p_boardModel->moveTile(position, next);
            if (TokenZones::pointInCenter(next))
            {
                assert_debug(!moved_to_center, "Double game over!");
                moved_to_center = true;
            }
        }
        return moved_to_center;
    }

    void GameScene::generateNextToken()
    {
        const TokenZones::TokenZone &currentTokenZone{ TokenZones::tokenZones[m_nextTokenPart] };

        log_debug_info("NextTokenPart: ", m_nextTokenPart);
        log_debug_info("zone: ", currentTokenZone.zone_start);

        // Generate the new token type
        const size_type newToken{ private_->token_type_generator_->getUInt(NumTokens) };

        // Calculate in wich tile zone offset is going to appear
        const size_type token_displacement{ private_->token_position_generator_->getUInt(currentTokenZone.size) };

        // Prepare the position for the new token
        const vector2dst new_position{TokenZones::displacedStartPoint(currentTokenZone, token_displacement)};
        lib::log_debug_info("New tile pos: ", new_position);

        // Now, we have the data for the new token generated, but first, lets start to move the row or col.
        const auto game_over = moveTowardsCenter(
                    m_boardGroup->p_boardModel, 
                    currentTokenZone.direction, new_position);

        // Set the new token
        m_boardGroup->createNewToken(
            static_cast<board::BoardTileData>(newToken),
            new_position,
            tileSize());

        // Select the next token zone.
        m_nextTokenPart = (m_nextTokenPart + 1) % NumWays;

        CLIENT_EXECUTE_IN_DEBUG(_debugDisplayBoard());

        if (game_over)
        {
            m_sceneStates->setState(GameSceneStates::GameOver);
        }
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
        m_player = m_boardGroup->m_mainBoardrg->createSceneNode<Player>("playerNode");
        m_player->setUp(TokenZones::centerRect.leftTop(), rectFromSize(tileSize()), board2SceneFactor());

        // Add it to the board and to the scene nodes
        m_boardGroup->p_boardModel->setTile(m_player->boardPosition(), m_player);
    }

    void GameScene::launchPlayer()
    {
        lib::log_debug_info("Launching player");
        const Direction loopDirection{ m_player->currentDirection() };
        const vector2dst loopPosition{ m_player->boardPosition() };
        const board::BoardTileData tokenType{ m_player->data.get() };
        u32 inARow{ 0 };
        for_each_token_in_line(loopPosition, loopDirection, [this, tokenType, &inARow](const vector2dst &loopPosition, const Direction &)
        {
            bool result{ true };
            bool found{ false };
            vector2df lastTokenPosition{};

            if (!m_boardGroup->p_boardModel->tileEmpty(loopPosition) && !TokenZones::pointInCenter(loopPosition) && result)
            {
                sptr<board::ITile> currentToken{ m_boardGroup->p_boardModel->getTile(loopPosition) };
                board::BoardTileData currentTokenType = currentToken->data.get();

                if (currentTokenType == tokenType) 
                {
                    // If we found a token with the same color than the player:

                    // Increment the number of tokens deleted in a row
                    ++inARow;
                    log_debug_info("In a row: ", inARow);

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

                    log_debug_info("Player type changed to ", m_player->data.get());

                    // Exit the loop
                    result = false;
                }
            }

            if (found)
            {
                log_debug_info("Tile with same color found");
                log_debug_info("Creating points to score");
                auto sceneNode(createSceneNode("pointIncrementScore_SceneNode"));

                auto renderizables_sceneNode = sceneNode->addComponentOfType<Renderizables>();
                auto node(renderizables_sceneNode->createNode("pointIncrementScore"));
                node->figType.set(FigType_t::Shape);
                node->pointCount.set(30U);
                node->box = rectFromSize(15.0f, 15.0f);
                node->color = colors::White;

                {
                    using namespace gameplay::constants;

                    log_debug_info("Creating animation for points to score");
                    private_->scene_animation_component_->
                        addPropertyAnimation(TimePoint_as_miliseconds(MillisAnimationPointsToScore),
                            sceneNode->position, lastTokenPosition, EndPositionPointsToScore,
                            [this, sceneNode]()
                            {
                                removeSceneNode(sceneNode);
                            }
                        );
                }
                log_debug_info("Launching player");
                m_player->launchAnimation(lastTokenPosition);
            }
            return result;
        });
        log_debug_info("Number of tokens in a row: ", inARow);
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
        for (u32 y{ 0 }; y < TokenZones::size.y; ++y)
        {
            str temp;
            for (u32 x{ 0 }; x < TokenZones::size.x; ++x)
            {
                str chTemp;
                auto lp_tile(m_boardGroup->p_boardModel->getTile({ x, y }));
                if (lp_tile) 
                {
                    chTemp = str::to_str(lp_tile->data.get());
                }
                else 
                {
                    chTemp = "*";
                    if (TokenZones::pointInCenter({ x, y }))
                    {
                        chTemp = "C";
                    }
                }

                temp += chTemp;
            }
            log_debug_info(temp);
        }
    }
}
