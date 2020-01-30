#include "gamescene.hpp"

#include "token.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "gameover.hpp"
#include "gamehud.hpp"
#include "pause.hpp"

#ifdef USE_DEBUG_ACTIONS
#include "debug_actions.hpp"
#endif

#include "../zoperprogramcontroller.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <boardmanager/include/boardmodel.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/renderizable.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/facades/include/resourcehandler.hpp>
#include <lib/scene/components/animationcomponent.hpp>
#include <lib/scene/components/inputcomponent.hpp>
#include <lib/scene/components/randomnumberscomponent.hpp>
#include <lib/system/scenemanager.hpp>

//TODO: Fixme
#include <lib/system/systemprovider.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;

constexpr u32 NumTokens = 5U;
constexpr u32 PlayerToken = NumTokens;

struct GameScene::GameScenePrivate
{
    sptr<AnimationComponent> scene_animation_component_;
    sptr<RandomNumbersComponent> token_type_generator_;
    sptr<RandomNumbersComponent> token_position_generator_;
};

GameScene::GameScene() : Scene{StaticTypeName} {}
GameScene::~GameScene() = default;

void GameScene::onCreated()
{
    BaseClass::onCreated();

    log_assert(private_ == nullptr, "Private data pointer is not nullptr!");
    private_ = new GameScenePrivate();

    dataWrapper<ResourceHandler>()->loadResources(GameResources{});

    using namespace lib::board;

    log_assert(!m_boardGroup, "m_boardGroup is not empty");
    m_boardGroup = createSceneNode<BoardGroup>("BoardGroup", TokenZones::size);

    addPlayer();

    m_nextTokenPart = 0U;

    auto inputComponent(addComponentOfType<scene::InputComponent>());
    inputComponent->KeyPressed.connect([this](const lib::Key &key) {
        DisplayLog::info("Key pressed in GameScene");
        // TODO: Fixme
        const auto &keyMapping = sceneManager().systemProvider().app<ZoperProgramController>().keyMapping;
        switch (m_sceneStates->currentState())
        {
        case GameSceneStates::Playing:
        {
            auto dir(keyMapping->getDirectionFromKey(key));
            if (dir.isValid())
            {
                m_player->movePlayer(dir);
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
            sceneManager().sceneController()->switchToNextScene();
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
    app<ZoperProgramController>().importGameSharedData(game_shared_data_);

    private_->scene_animation_component_ = addComponentOfType<scene::AnimationComponent>();
    // At this point, we setup level properties.
    // level_properties_ should not be used before this point.
    level_properties_ = addComponentOfType<LevelProperties>();
    level_properties_->levelChanged.connect([this](const auto level) {
        // Forward current level where necessary.
        m_boardGroup->setLevel(level);
    });

    level_properties_->setUp(
        game_shared_data_->startLevel,
        game_shared_data_->gameMode,
        m_sceneTimerComponent);

    m_boardGroup->setUp(level_properties_);

#ifdef USE_DEBUG_ACTIONS
    addComponentOfType<DebugActions>();
#endif

    m_nextTokenTimer = m_sceneTimerComponent->addTimer(
        TimerType::Continuous,
        TimePoint_as_miliseconds(level_properties_->millisBetweenTokens()),
        [this](TimePoint realEllapsed) {
            DisplayLog::info("Elapsed between tokens: ", realEllapsed.milliseconds());
            // New token
            generateNextToken();
        });

    m_gameOver = createSceneNode<GameOverSceneNode>("gameOverSceneNode");
    m_gameOver->visible = false;

    // Set state controll.
    {
        m_sceneStates = addComponentOfType<std::remove_reference_t<decltype(*m_sceneStates)>>();

        StatesControllerActuatorRegister<GameSceneStates> gameSceneActuatorRegister;
        gameSceneActuatorRegister.registerStatesControllerActuator(*m_sceneStates, *this);
    }

    private_->token_type_generator_ = addComponentOfType<RandomNumbersComponent>();
    log_assert(private_->token_type_generator_ != nullptr, "Cannot create DataProviderComponent");
    private_->token_position_generator_ = private_->token_type_generator_; //addComponentOfType<DataProviderComponent>();
    log_assert(private_->token_position_generator_ != nullptr, "Cannot create DataProviderComponent");

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

void GameScene::onEnterState(const GameSceneStates &state)
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
    DisplayLog::info("Entered state: ", make_str(state));
}

void GameScene::onExitState(const GameSceneStates &state)
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
    DisplayLog::info("Exited state: ", make_str(state));
}

void GameScene::setLevel(const size_type)
{
    m_boardGroup->setLevel(game_shared_data_->endLevel);
}

bool moveTowardsCenter(
    const sptr<board::BoardModelComponent> &p_boardModel,
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
            log_assert(!moved_to_center, "Double game over!");
            moved_to_center = true;
        }
    }
    return moved_to_center;
}

void GameScene::generateNextToken()
{
    const TokenZones::TokenZone &currentTokenZone{TokenZones::tokenZones[m_nextTokenPart]};

    DisplayLog::info("NextTokenPart: ", m_nextTokenPart);
    DisplayLog::info("zone: ", currentTokenZone.zone_start);

    // Generate the new token type
    const size_type newToken{private_->token_type_generator_->getUInt(NumTokens)};

    // Calculate in wich tile zone offset is going to appear
    const size_type token_displacement{private_->token_position_generator_->getUInt(currentTokenZone.size)};

    // Prepare the position for the new token
    const vector2dst new_position{TokenZones::displacedStartPoint(currentTokenZone, token_displacement)};
    lib::DisplayLog::info("New tile pos: ", new_position);

    // Now, we have the data for the new token generated, but first,
    /// lets start to move the row or col.
    const auto game_over = moveTowardsCenter(
        m_boardGroup->boardModel(),
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
        goGameOver();
    }
}

void GameScene::goGameOver()
{
    level_properties_->updateGameSharedData(game_shared_data_);
    m_sceneStates->setState(GameSceneStates::GameOver);
}

void GameScene::for_each_token_in_line(const vector2dst &startPosition, const Direction &direction,
                                       function<bool(const vector2dst &, const Direction &)> updatePredicate)
{
    vector2dst loopPosition{startPosition};

    // Now, we have the data for the new token generated, but first, lets start to move the row or col.
    bool stay{true};
    do
    {
        stay &= updatePredicate(loopPosition, direction);
        loopPosition = direction.applyToVector(loopPosition);
        stay &= m_boardGroup->boardModel()->validCoords(loopPosition);
    } while (stay);
}

void GameScene::addPlayer()
{
    DisplayLog::info("Adding player tile at ", TokenZones::centerRect.leftTop());
    log_assert(!m_player, "Player already initialized");
    // Create the player instance
    m_player = m_boardGroup->tokensSceneNode()->createSceneNode<Player>("playerNode");
    m_player->configure(TokenZones::centerRect.leftTop(),
        rectFromSize(tileSize()), board2SceneFactor());

    // Add it to the board and to the scene nodes
    m_boardGroup->boardModel()->setTile(m_player->boardPosition(), m_player);
}

void GameScene::launchPlayer()
{
    lib::DisplayLog::info("Launching player");
    const Direction loopDirection{m_player->currentDirection()};
    const vector2dst loopPosition{m_player->boardPosition()};
    const board::BoardTileData tokenType{m_player->data.get()};
    u32 inARow{0};
    for_each_token_in_line(loopPosition, loopDirection, [this, tokenType, &inARow](const vector2dst &loopPosition, const Direction &) {
        bool result{true};
        bool found{false};
        vector2df lastTokenPosition{};

        if (!m_boardGroup->boardModel()->tileEmpty(loopPosition) && !TokenZones::pointInCenter(loopPosition) && result)
        {
            sptr<board::ITile> currentToken{m_boardGroup->boardModel()->getTile(loopPosition)};
            board::BoardTileData currentTokenType = currentToken->data.get();

            if (currentTokenType == tokenType)
            {
                // If we found a token with the same color than the player:

                // Increment the number of tokens deleted in a row
                ++inARow;
                DisplayLog::info("In a row: ", inARow);

                // Increase the score accordingly
                level_properties_->increaseScore(inARow * level_properties_->baseScore());

                // Inform that a token has been consumed
                level_properties_->tokenConsumed();

                // Store the position of this last cosumed token
                lastTokenPosition = board2Scene(loopPosition);

                // Delete the token
                m_boardGroup->boardModel()->deleteTile(loopPosition);

                // At least you found one token
                found = true;
            }
            else
            {
                // If we found a token, but it is from another color:

                // Change the type of the player to this new one
                m_boardGroup->boardModel()->changeTileData(m_player->boardPosition(), currentTokenType);

                // Change the type of the token for the previous type of the player
                m_boardGroup->boardModel()->changeTileData(loopPosition, tokenType);

                DisplayLog::info("Player type changed to ", m_player->data.get());

                // Exit the loop
                result = false;
            }
        }

        if (found)
        {
            DisplayLog::info("Tile with same color found");
            DisplayLog::info("Creating points to score");
            auto sceneNode(createSceneNode("pointIncrementScore_SceneNode"));

            auto node(createRenderizable(
                "pointIncrementScore", FigType_t::Shape,
                rectFromSize(15.0F, 15.0F), colors::White, 30U));

            {
                using namespace gameplay::constants;

                DisplayLog::info("Creating animation for points to score");
                private_->scene_animation_component_->addPropertyAnimation(
                    TimePoint_as_miliseconds(MillisAnimationPointsToScore),
                    sceneNode->position,
                    lastTokenPosition, EndPositionPointsToScore,
                    [this, sceneNode]()
                    {
                        removeSceneNode(sceneNode);
                    });
            }
            DisplayLog::info("Launching player");
            m_player->launchAnimation(lastTokenPosition);
        }
        return result;
    });
    DisplayLog::info("Number of tokens in a row: ", inARow);
}

vector2df GameScene::board2SceneFactor() const
{
    return {sceneManager().viewRect().size().x / static_cast<f32>(m_boardGroup->boardModel()->size().x),
            sceneManager().viewRect().size().y / static_cast<f32>(m_boardGroup->boardModel()->size().y)};
}

vector2df GameScene::board2Scene(const lib::vector2dst &bPosition) const
{
    const auto b2sf{board2SceneFactor()};
    return {b2sf.x * bPosition.x, b2sf.y * bPosition.y};
}

vector2df GameScene::tileSize() const
{
    return board2Scene({1, 1});
}

void GameScene::_debugDisplayBoard() const
{
    for (u32 y{0}; y < TokenZones::size.y; ++y)
    {
        str temp;
        for (u32 x{0}; x < TokenZones::size.x; ++x)
        {
            str chTemp;
            auto lp_tile(m_boardGroup->boardModel()->getTile({x, y}));
            if (lp_tile)
            {
                chTemp = str::to_str(lp_tile->data.get());
            }
            else
            {
                chTemp = "*";
                if (TokenZones::pointInCenter({x, y}))
                {
                    chTemp = "C";
                }
            }

            temp += chTemp;
        }
        DisplayLog::info(temp);
    }
}
} // namespace zoper
