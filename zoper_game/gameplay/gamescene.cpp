#include "gamescene.hpp"

#include "token.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "gameover.hpp"
#include "gamehud.hpp"
#include "pause.hpp"
#include "boardutils.hpp"
#include "scoreutils.hpp"

#ifdef USE_DEBUG_ACTIONS
#include "debug_actions.hpp"
#endif

#include "../zoperprogramcontroller.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <boardmanager/include/boardmodel.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <lib/resources/include/resourcehandler.hpp>
#include <lib/scene_components/include/animationcomponent.hpp>
#include <lib/scene_components/include/scenecontrol.hpp>
#include <lib/input/include/inputcomponent.hpp>
#include <lib/random/include/randomnumberscomponent.hpp>
#include <lib/shareddata/include/shareddataview.hpp>

using namespace mtps;
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;

namespace zoper
{
constexpr u32 NumTokens   = 5U;
constexpr u32 PlayerToken = NumTokens;

struct GameScene::GameScenePrivate
{
    sptr<AnimationComponent> scene_animation_component_;
    sptr<rnd::RandomNumbersComponent> token_type_generator_;
    sptr<rnd::RandomNumbersComponent> token_position_generator_;

    void createScoreIncrementPoints(SceneNode& main_node,
                                    const vector2df& lastTokenPosition)
    {
        auto sceneNode =
            main_node.createSceneNode("pointIncrementScore_SceneNode");

        auto node(sceneNode->createRenderizable(
            "pointIncrementScore", FigType_t::Shape, rectFromSize(15.0F, 15.0F),
            colors::White, 30U));

        {
            using namespace gameplay::constants;

            DisplayLog::info("Creating animation for points to score");
            scene_animation_component_->addPropertyAnimation(
                time::TimePoint_as_miliseconds(MillisAnimationPointsToScore),
                sceneNode->position, lastTokenPosition,
                EndPositionPointsToScore,
                Animation::AnimationDirection::Forward, [this, sceneNode]() {
                    sceneNode->parent()->removeSceneNode(sceneNode);
                });
        }
    }
};

GameScene::GameScene() : Scene{StaticTypeName}
{}
GameScene::~GameScene() = default;

void GameScene::onCreated()
{
    BaseClass::onCreated();

    log_assert(private_ == nullptr, "Private data pointer is not nullptr!");
    private_ = muptr<GameScenePrivate>();

    dataWrapper<ResourceHandler>()->loadResources(GameResources{});

    using namespace lib::board;

    log_assert(!m_boardGroup, "m_boardGroup is not empty");
    m_boardGroup = createSceneNode<BoardGroup>("BoardGroup", TokenZones::size);

    m_nextTokenPart = 0U;

    auto inputComponent(addComponentOfType<input::InputComponent>());
    inputComponent->KeyPressed.connect([this](const lib::input::Key& key) {
        DisplayLog::info("Key pressed in GameScene");
        // TODO: Fixme
        KeyMapping keyMapping__;
        KeyMapping* keyMapping = &keyMapping__;
        //        const auto &keyMapping =
        //        sceneManager().systemProvider().app<ZoperProgramController>().keyMapping;
        switch (m_sceneStates->currentState())
        {
        case GameSceneStates::Playing: {
            auto dir(keyMapping->getDirectionFromKey(key));
            if (dir.isValid())
            {
                m_boardGroup->player()->movePlayer(dir);
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
            dataWrapper<SceneControl>()->switchToNextScene();
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
    scene_timer_component_ = addComponentOfType<time::TimerComponent>();

    private_->scene_animation_component_ =
        addComponentOfType<AnimationComponent>();

    // At this point, we setup level properties.
    // level_properties_ should not be used before this point.
    level_properties_ = addComponentOfType<LevelProperties>();
    level_properties_->levelChanged.connect([this](const auto level) {
        // Forward current level where necessary.
        m_boardGroup->setLevel(level);
    });

    size_type start_level;
    GameMode game_mode;

    {
        auto game_shared_data_view = dataWrapper<shdata::SharedDataView>();
        auto& game_shared_data =
            game_shared_data_view->dataAs<GameSharedData>();

        start_level = game_shared_data.startLevel;
        game_mode   = game_shared_data.gameMode;
    }

    level_properties_->configure(start_level, game_mode,
                                 scene_timer_component_);

    m_boardGroup->configure(level_properties_);

#ifdef USE_DEBUG_ACTIONS
    addComponentOfType<DebugActions>();
#endif

    m_nextTokenTimer = scene_timer_component_->addTimer(
        time::TimerType::Continuous,
        time::TimePoint_as_miliseconds(
            level_properties_->millisBetweenTokens()),
        [this](time::TimePoint realEllapsed) {
            DisplayLog::info("Elapsed between tokens: ",
                             realEllapsed.milliseconds());
            // New token
            generateNextToken();
        });

    m_gameOver = createSceneNode<GameOverSceneNode>("gameOverSceneNode");
    m_gameOver->visible = false;

    // Set state control.
    {
        m_sceneStates = addComponentOfType<
            std::remove_reference_t<decltype(*m_sceneStates)>>();

        StatesControllerActuatorRegister<GameSceneStates>
            gameSceneActuatorRegister;
        gameSceneActuatorRegister.registerStatesControllerActuator(
            *m_sceneStates, *this);
    }

    private_->token_type_generator_ =
        addComponentOfType<rnd::RandomNumbersComponent>();
    log_assert(private_->token_type_generator_ != nullptr,
               "Cannot create DataProviderComponent");
    private_->token_position_generator_ = private_->token_type_generator_;
    log_assert(private_->token_position_generator_ != nullptr,
               "Cannot create DataProviderComponent");

    // Prepare the pause text.
    pause_node_ = createSceneNode<PauseSceneNode>("PauseNode");

    m_sceneStates->start(GameSceneStates::Playing);
}

void GameScene::onEnterState(const GameSceneStates& state)
{
    switch (state)
    {
    case GameSceneStates::Pause: {
        scene_timer_component_->pause();
        pause_node_->enterPause();
    }
    break;
    case GameSceneStates::GameOver:
        m_gameOver->visible = true;
        scene_timer_component_->pause();
        break;
    default:
        break;
    }
    DisplayLog::info("Entered state: ", make_str(state));
}

void GameScene::onExitState(const GameSceneStates& state)
{
    switch (state)
    {
    case GameSceneStates::Pause: {
        scene_timer_component_->resume();
        pause_node_->exitPause();
    }
    break;
    default:
        break;
    }
    DisplayLog::info("Exited state: ", make_str(state));
}

bool moveTowardsCenter(
    const sptr<board::BoardModelComponent>& board_model,
    const Direction direction,
    const vector2dst position)
{
    bool moved_to_center{false};

    // Is the current tile position empty?
    if (!board_model->tileEmpty(position))
    {
        // If not, what about the next position to check, is empty?
        const auto next = direction.applyToVector(position);

        if (!board_model->tileEmpty(next))
        {
            // If the target position where to move the
            // token is occupied, move the this target first.
            moved_to_center = moveTowardsCenter(board_model, direction, next);
        }
        board_model->moveTile(position, next);
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
    const TokenZones::TokenZone& currentTokenZone{
        TokenZones::tokenZones[m_nextTokenPart]};

    DisplayLog::info("NextTokenPart: ", m_nextTokenPart);
    DisplayLog::info("zone: ", currentTokenZone.zone_start);

    // Generate the new token type
    const size_type newToken{
        private_->token_type_generator_->getUInt(NumTokens)};

    // Calculate in wich tile zone offset is going to appear
    const size_type token_displacement{
        private_->token_position_generator_->getUInt(currentTokenZone.size)};

    // Prepare the position for the new token
    const vector2dst new_position{
        TokenZones::displacedStartPoint(currentTokenZone, token_displacement)};
    lib::DisplayLog::info("New tile pos: ", new_position);

    // Now, we have the data for the new token generated, but first,
    /// lets start to move the row or col.
    const auto game_over = moveTowardsCenter(
        m_boardGroup->boardModel(), currentTokenZone.direction, new_position);

    // Set the new token
    m_boardGroup->createNewToken(static_cast<board::BoardTileData>(newToken),
                                 new_position, tileSize());

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
    m_sceneStates->setState(GameSceneStates::GameOver);
}

void GameScene::launchPlayer()
{
    lib::DisplayLog::info("Launching player");
    const Direction loopDirection{m_boardGroup->player()->currentDirection()};
    const vector2dst loopPosition{
        m_boardGroup->player()->boardPosition()};
    const board::BoardTileData tokenType{m_boardGroup->player()->data.get()};
    ScoreIncrementer score_incrementer{level_properties_};
    BoardUtils::for_each_token_in_line(
        loopPosition, loopDirection, m_boardGroup->boardModel()->size(),
        [this, tokenType, &score_incrementer](
            const vector2dst& loopPosition, const Direction&) {
            bool result{true};
            bool found{false};
            vector2df lastTokenPosition{};

            if (!m_boardGroup->boardModel()->tileEmpty(loopPosition) &&
                !TokenZones::pointInCenter(loopPosition) && result)
            {
                sptr<board::ITile> currentToken{
                    m_boardGroup->boardModel()->getTile(loopPosition)};
                board::BoardTileData currentTokenType{currentToken->data.get()};

                if (currentTokenType == tokenType)
                {
                    // If we found a token with the same color than the player:

                    // Increment the number of tokens deleted in a row
                    score_incrementer.addHit();

                    // Store the position of this last cosumed token
                    lastTokenPosition = m_boardGroup->board2Scene(loopPosition);

                    // Delete the token
                    m_boardGroup->boardModel()->deleteTile(loopPosition);

                    // At least you found one token
                    found = true;
                }
                else
                {
                    // If we found a token, but it is from another color:

                    // Change the type of the player to this new one and
                    // change the type of the token for the previous type of the
                    // player
                    m_boardGroup->boardModel()->swapTileData(
                        m_boardGroup->player()->boardPosition(), loopPosition);

                    DisplayLog::info("Player type changed to ",
                                     m_boardGroup->player()->data.get());

                    // Exit the loop
                    result = false;
                }
            }

            if (found)
            {
                DisplayLog::info("Tile with same color found");
                DisplayLog::info("Creating points to score");
                private_->createScoreIncrementPoints(*this, lastTokenPosition);

                DisplayLog::info("Launching player");
                m_boardGroup->player()->launchAnimation(lastTokenPosition);
            }
            return result;
        });
}

vector2df GameScene::tileSize() const
{
    return m_boardGroup->tileSize();
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
}  // namespace zoper
