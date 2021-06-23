#include "gamescene.hpp"

#include "token.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "gameover.hpp"
#include "gamehud.hpp"
#include "pause.hpp"
#include "boardutils.hpp"
#include "scoreutils.hpp"
#include "next_token.hpp"

#ifdef USE_DEBUG_ACTIONS
#include "debug_actions.hpp"
#endif

#include "../zoperprogramcontroller.hpp"
#include "../keymapping.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>

#include <boardmanager/include/boardmanager.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/scene/componentcontainer.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene_components/animationcomponent.hpp>
#include <haf/include/scene_components/scenecontrol.hpp>
#include <haf/include/input/inputcomponent.hpp>
#include <haf/include/random/randomnumberscomponent.hpp>
#include <haf/include/shareddata/shareddataupdater.hpp>
#include <haf/include/shareddata/shareddataviewer.hpp>
#include <haf/include/resources/iresourceconfigurator.hpp>
#include <haf/include/system/interfaceaccess.hpp>
#include <htypes/include/serializer.hpp>
#include <haf/include/filesystem/fileserializer.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>

using namespace htps;
using namespace haf;
using namespace haf::render;
using namespace haf::scene;
using namespace haf::scene::nodes;

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
        auto renderizableSceneNode =
            main_node.createSceneNode<RenderizablesSceneNode>(
                "pointIncrementScore_SceneNode");

        auto node = renderizableSceneNode->renderizableBuilder()
                        .name("pointIncrementScore")
                        .figType(FigType_t::Shape)
                        .box(rectFromSize(15.0F, 15.0F))
                        .color(colors::White)
                        .pointCount(30U)
                        .create();

        {
            using namespace gameplay::constants;

            DisplayLog::info("Creating animation for points to score");
            scene_animation_component_->addPropertyAnimation(
                time::TimePoint_as_miliseconds(MillisAnimationPointsToScore),
                renderizableSceneNode->prop<haf::scene::Position>(),
                lastTokenPosition, EndPositionPointsToScore,
                Animation::AnimationDirection::Forward,
                [this, renderizableSceneNode]() {
                    renderizableSceneNode->parentAs<SceneNode>()
                        ->removeSceneNode(renderizableSceneNode);
                });
        }
    }
    uptr<KeyMapping> key_mapping_;
};

GameScene::GameScene() : Scene{StaticTypeName}
{}

GameScene::~GameScene() = default;

str GameScene::nextSceneName()
{
    return HIGHSCORES_SCENE_NAME;
}

void GameScene::onCreated()
{
    BaseClass::onCreated();

    LogAsserter::log_assert(p_ == nullptr,
                            "Private data pointer is not nullptr!");
    p_ = muptr<GameScenePrivate>();

    auto& resources_configurator =
        systemInterface<res::IResourcesConfigurator>();
    resources_configurator.setResourceConfigFile("resources.txt");
    resources_configurator.loadSection("game");

    using namespace haf::board;

    LogAsserter::log_assert(!m_boardGroup, "m_boardGroup is not empty");
    m_boardGroup = createSceneNode<BoardGroup>("BoardGroup");
    //    m_boardGroup->token_hit.connect(&(this->tokenHitAnimation));

    next_token_part_ = 0U;

    // Connect to key press funtion
    auto inputComponent(
        components().addComponentOfType<input::InputComponent>());
    inputComponent->KeyPressed.connect(
        make_function(this, &GameScene::keyPressed));

    // Create the general timer component for the scene.
    scene_timer_component_ =
        components().addComponentOfType<time::TimerComponent>();

    p_->scene_animation_component_ =
        components().addComponentOfType<AnimationComponent>();

    // At this point, we setup level properties.
    // level_properties_ should not be used before this point.
    level_properties_ = components().addComponentOfType<LevelProperties>();

    size_type start_level;
    GameMode game_mode;

    {
        auto game_shared_data =
            dataWrapper<shdata::SharedDataViewer<GameSharedData>>()->view(
                GameSharedData::address());

        start_level = game_shared_data->startLevel;
        game_mode   = game_shared_data->gameMode;
    }

    level_properties_->configure(start_level, game_mode,
                                 scene_timer_component_);

    m_boardGroup->configure(TokenZones::size, level_properties_);

#ifdef USE_DEBUG_ACTIONS
    components().addComponentOfType<DebugActions>();
#endif

    // The next token has the responsibility of calling the function
    // generate new tokens according with the time provided by level proverties
    next_token_ = msptr<NextToken>(scene_timer_component_);
    next_token_->prepareNextToken(
        make_function(level_properties_.get(),
                      &LevelProperties::millisBetweenTokens),
        [this]() { generateNextToken(); });

    // Prepare the game over text
    game_over_scene_node_ =
        createSceneNode<GameOverSceneNode>("gameOverSceneNode");
    game_over_scene_node_->prop<Visible>().set(false);

    // Prepare the pause text.
    pause_node_ = createSceneNode<PauseSceneNode>("PauseNode");

    // Set state control.
    {
        components().ensureComponentOfType(m_sceneStates);

        StatesControllerActuatorRegister<GameSceneStates>
            gameSceneActuatorRegister;
        gameSceneActuatorRegister.registerStatesControllerActuator(
            *m_sceneStates, *this);
    }

    p_->token_type_generator_ =
        components().addComponentOfType<rnd::RandomNumbersComponent>();
    LogAsserter::log_assert(p_->token_type_generator_ != nullptr,
                            "Cannot create DataProviderComponent");
    p_->token_position_generator_ = p_->token_type_generator_;
    LogAsserter::log_assert(p_->token_position_generator_ != nullptr,
                            "Cannot create DataProviderComponent");

    p_->key_mapping_ = muptr<KeyMapping>();
    p_->key_mapping_->reset();

    dataWrapper<sys::FileSerializer>()->deserializeFromFile("keys.txt",
                                                            *p_->key_mapping_);
    dataWrapper<sys::FileSerializer>()->serializeToFile("keys.txt",
                                                        *p_->key_mapping_);

    m_sceneStates->start(GameSceneStates::Playing);
}

void GameScene::onEnterState(const GameSceneStates& state)
{
    switch (state)
    {
        case GameSceneStates::Playing:
        {
        }
        break;

        case GameSceneStates::Pause:
        {
            scene_timer_component_->pause();
            pause_node_->enterPause();
        }
        break;
        case GameSceneStates::GameOver:
        {
            game_over_scene_node_->prop<Visible>().set(true);
            scene_timer_component_->pause();
        }
        break;
    }
    DisplayLog::info("Entered state: ", make_str(state));
}

void GameScene::onExitState(const GameSceneStates& state)
{
    switch (state)
    {
        case GameSceneStates::Playing:
        {
        }
        break;

        case GameSceneStates::Pause:
        {
            scene_timer_component_->resume();
            pause_node_->exitPause();
        }
        break;

        case GameSceneStates::GameOver:
        {
        }
        break;
    }
    DisplayLog::info("Exited state: ", make_str(state));
}

void GameScene::generateNextToken()
{
    const TokenZones::TokenZone& currentTokenZone{
        TokenZones::tokenZones[next_token_part_]};

    DisplayLog::info("NextTokenPart: ", next_token_part_);
    DisplayLog::info("zone: ", currentTokenZone.zone_start);

    // Generate the new token type
    size_type const newToken{p_->token_type_generator_->getUInt(NumTokens)};

    // Calculate in wich tile zone offset is going to appear
    size_type const token_displacement{
        p_->token_position_generator_->getUInt(currentTokenZone.size)};

    // Prepare the position for the new token
    vector2dst const new_position{
        TokenZones::displacedStartPoint(currentTokenZone, token_displacement)};
    haf::DisplayLog::info("New tile pos: ", new_position);

    // Now, we have the data for the new token generated, but first,
    /// lets start to move the row or col.
    const auto game_over = m_boardGroup->moveTowardsCenter(
        currentTokenZone.direction, new_position);

    // Set the new token
    m_boardGroup->createNewToken(
        static_cast<BoardGroup::BoardTileData>(newToken), new_position,
        m_boardGroup->tileSize());

    // Select the next token zone.
    next_token_part_ = ((next_token_part_ + 1U) % NumWays);

    DisplayLog::debug(m_boardGroup->boardManager()->toStr());

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
    haf::DisplayLog::info("Launching player");
    const Direction loopDirection{m_boardGroup->player()->currentDirection()};
    const vector2dst loopPosition{m_boardGroup->player()->boardPosition()};
    auto const tokenType{m_boardGroup->player()->value()};
    ScoreIncrementer score_incrementer{level_properties_};
    vector2df lastTokenPosition{};

    BoardUtils::for_each_coordinate_in_rect(
        loopPosition, loopDirection, m_boardGroup->boardManager()->size(),
        [this, tokenType, &score_incrementer, &lastTokenPosition](
            const vector2dst& loopPosition, const Direction&) {
            bool result{true};
            bool found{false};

            if (!m_boardGroup->boardManager()->tileEmpty(loopPosition) &&
                TokenZones::toBoardBackgroundType(
                    m_boardGroup->boardManager()->backgroundData(
                        loopPosition)) !=
                    TokenZones::BoardBackgroundType::Center)
            {
                sptr<board::ITile> currentToken{
                    m_boardGroup->boardManager()->getTile(loopPosition)};
                auto const currentTokenType{currentToken->value()};

                if (currentTokenType == tokenType)
                {
                    // If we found a token with the same color than the player:

                    // Increment the number of tokens deleted in a row
                    score_incrementer.addHit();

                    // Delete the token
                    m_boardGroup->boardManager()->deleteTile(loopPosition);

                    // At least you found one token
                    found = true;
                }
                else
                {
                    // If we found a token, but it is from another color:

                    // Change the type of the player to this new one and
                    // change the type of the token for the previous type of the
                    // player
                    m_boardGroup->boardManager()->swapTileData(
                        m_boardGroup->player()->boardPosition(), loopPosition);

                    DisplayLog::info("Player type changed to ",
                                     m_boardGroup->player()->value());

                    // Exit the loop
                    result = false;
                }
            }

            // Store the position of this last cosumed token
            lastTokenPosition = m_boardGroup->board2Scene(loopPosition);

            if (found)
            {
                DisplayLog::info("Tile with same color found");
                DisplayLog::info("Creating points to score");
                p_->createScoreIncrementPoints(*this, lastTokenPosition);
            }
            return result;
        });
    DisplayLog::info("Launching player");
    m_boardGroup->player()->launchAnimation(lastTokenPosition);
}

void GameScene::tokenHitAnimation(vector2dst const& pos)
{
    auto const lastTokenPosition = m_boardGroup->board2Scene(pos);
    p_->createScoreIncrementPoints(*this, lastTokenPosition);
}

void GameScene::keyPressed(input::Key const key)
{
    DisplayLog::info("Key pressed in GameScene");
    // TODO: Fixme
    KeyMapping keyMapping__;
    KeyMapping* keyMapping = &keyMapping__;

    switch (m_sceneStates->currentState())
    {
        case GameSceneStates::Playing:
        {
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
        {
            dataWrapper<SceneControl>()->switchToNextScene();
        }
        break;

        case GameSceneStates::Pause:
        {
            if (keyMapping->isPauseKey(key))
            {
                m_sceneStates->setState(GameSceneStates::Playing);
            }
        }
        break;
    }
}

}  // namespace zoper
