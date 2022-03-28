#include "gamescene.hpp"
#include "gamescene_private.hpp"

#include "token.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "gameover.hpp"
#include "pause_scene_node.hpp"
#include "boardutils.hpp"
#include "scoreutils.hpp"
#include "next_token.hpp"
#include "player_launcher.hpp"
#include "gamescene_input.hpp"

#ifdef USE_DEBUG_ACTIONS
#include <haf/include/debug_utils/debug_actions.hpp>
#endif

#include "../zoperprogramcontroller.hpp"
#include "../keymapping.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>

#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/board_types.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene_components/iscene_control.hpp>
#include <haf/include/scene_components/statescontrolleractuator_register.hpp>
#include <haf/include/shareddata/shared_data_viewer.hpp>
#include <haf/include/resources/iresource_configurator.hpp>
#include <htypes/include/serializer.hpp>
#include <haf/include/filesystem/ifile_serializer.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include "../static_data.hpp"

using namespace htps;
using namespace haf;
using namespace haf::render;
using namespace haf::scene;
using namespace haf::scene::nodes;
using namespace haf::anim;

namespace zoper
{
constexpr u32 NumTokens = 5U;

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
    //    componentOfType<CameraComponent>()->view = DefaultView;
    cameraComponent()->view = SceneBox{-0.5F, -0.5F, 1.0F, 1.0F};
    //    cameraComponent()->view = SceneBox{-250.0F, -250.0F, 500.0F, 500.0F};
    //        cameraComponent()->view = SceneBox{-1000.0F, -1000.0F, 2000.0F,
    //        2000.0F};

    LogAsserter::log_assert(p_ == nullptr,
                            "Private data pointer is not nullptr!");
    p_ = muptr<GameScenePrivate>();

    auto resources_configurator{subSystem<res::IResourcesConfigurator>()};
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->loadSection("game");

    next_token_part_ = 0U;

    // Create the general timer component for the scene.
    scene_timer_component_ = component<time::TimerComponent>();

    p_->scene_animation_component_ = component<AnimationComponent>();

    // At this point, we setup level properties.
    // level_properties_ should not be used before this point.
    level_properties_ = component<LevelProperties>();

    size_type start_level;
    GameMode game_mode;

    {
        auto game_shared_data{shdata::SharedDataViewer<GameSharedData>(
                                  subSystem<shdata::ISharedData>())
                                  .view(GameSharedData::address())};

        start_level = game_shared_data->startLevel;
        game_mode   = game_shared_data->gameMode;
    }

    level_properties_->configure(start_level, game_mode,
                                 scene_timer_component_);

    using namespace haf::board;

    LogAsserter::log_assert(!board_group_, "board_group_ is not empty");
    board_group_ = createSceneNode<BoardGroup>("BoardGroup");

    board_group_->configure(TokenZones::size, level_properties_);

    moveToFirstPosition(board_group_);
#ifdef USE_DEBUG_ACTIONS
    component<debug::DebugActions>()->addDebugAction(
        input::Key::Num2,
        [this]() { component<debug::DebugActions>()->logSceneNodeTree(); });
    component<debug::DebugActions>()->addDebugAction(
        input::Key::Num1, [this]() { levelProperties()->increaseScore(100U); });
    component<debug::DebugActions>()->addDebugAction(
        input::Key::Q, [this]() { goGameOver(); });
    component<debug::DebugActions>()->addDebugAction(
        input::Key::A, [this]() { levelProperties()->nextLevel(); });

#endif

    // The next token has the responsibility of calling the function
    // generate new tokens according with the time provided by level proverties
    next_token_ = msptr<NextToken>(scene_timer_component_);
    next_token_->prepareNextToken(
        make_function(level_properties_.get(),
                      &LevelProperties::millisBetweenTokens),
        [this]() { generateNextToken(); });

    p_->states_manager_ = muptr<GameSceneStateManager>(
        scene_timer_component_, createSceneNode<PauseSceneNode>("PauseNode"),
        createSceneNode<GameOverSceneNode>("gameOverSceneNode"));

    // Set state control.
    {
        component(scene_states_);

        StatesControllerActuatorRegister<GameSceneStates>
            gameSceneActuatorRegister;
        gameSceneActuatorRegister.registerStatesControllerActuator(
            *scene_states_, *(p_->states_manager_));
    }

    p_->token_type_generator_ = component<rnd::RandomNumbersComponent>();
    LogAsserter::log_assert(p_->token_type_generator_ != nullptr,
                            "Cannot create RandomNumbersComponent");

    p_->token_position_generator_ = p_->token_type_generator_;
    LogAsserter::log_assert(p_->token_position_generator_ != nullptr,
                            "Cannot create RandomNumbersComponent");

    auto game_scene_input{component<GameSceneInput>()};

    p_->key_mapping_ = muptr<KeyMapping>();
    p_->key_mapping_->reset();

    subSystem<sys::IFileSerializer>()->deserializeFromFile("keys.txt",
                                                           *p_->key_mapping_);
    subSystem<sys::IFileSerializer>()->serializeToFile("keys.txt",
                                                       *p_->key_mapping_);

    scene_states_->start(GameSceneStates::Playing);
    installDebugUtils();
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
    const auto game_over{board_group_->moveTowardsCenter(
        currentTokenZone.direction, new_position)};

    // Set the new token
    board_group_->createNewToken(
        static_cast<BoardGroup::BoardTileData>(newToken), new_position);

    // Select the next token zone.
    next_token_part_ = ((next_token_part_ + 1U) % NumWays);

    DisplayLog::debug(board_group_->boardManager()->toStr());

    if (game_over)
    {
        goGameOver();
    }
}

void GameScene::goGameOver()
{
    scene_states_->setState(GameSceneStates::GameOver);
}

void GameScene::launchPlayer()
{
    haf::DisplayLog::info("Launching player");
    ScoreIncrementer score_incrementer{level_properties_};

    PlayerLauncher player_launcher;
    player_launcher(score_incrementer, board_group_,
                    htps::make_function(this, &GameScene::tokenHitAnimation));
}

void GameScene::tokenHitAnimation(board::BoardPositionType const& pos)
{
    auto const lastTokenPosition = board_group_->board2Scene(pos);
    p_->createScoreIncrementPoints(*this, lastTokenPosition);
}

}  // namespace zoper
