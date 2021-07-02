#include "gamescene.hpp"
#include "gamescene_private.hpp"

#include "token.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "gameover.hpp"
#include "gamehud.hpp"
#include "pause.hpp"
#include "boardutils.hpp"
#include "scoreutils.hpp"
#include "next_token.hpp"
#include "player_launcher.hpp"
#include "gamescene_input.hpp"

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
#include <haf/include/scene_components/scenecontrol.hpp>
#include <haf/include/shareddata/shareddataupdater.hpp>
#include <haf/include/shareddata/shareddataviewer.hpp>
#include <haf/include/resources/resourceconfigurator.hpp>
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

    auto resources_configurator =
        dataWrapper<res::ResourcesConfigurator>();
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->loadSection("game");

    using namespace haf::board;

    LogAsserter::log_assert(!m_boardGroup, "m_boardGroup is not empty");
    m_boardGroup = createSceneNode<BoardGroup>("BoardGroup");
    //    m_boardGroup->token_hit.connect(&(this->tokenHitAnimation));

    next_token_part_ = 0U;

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
    {
        auto game_over_scene_node =
            createSceneNode<GameOverSceneNode>("gameOverSceneNode");
        game_over_scene_node->prop<Visible>().set(false);

        p_->m_states_manager = muptr<GameSceneStateManager>(
            scene_timer_component_, createSceneNode<PauseSceneNode>("PauseNode"),
            std::move(game_over_scene_node));
    }

    // Set state control.
    {
        components().ensureComponentOfType(m_sceneStates);

        StatesControllerActuatorRegister<GameSceneStates>
            gameSceneActuatorRegister;
        gameSceneActuatorRegister.registerStatesControllerActuator(
            *m_sceneStates, *(p_->m_states_manager));
    }

    p_->token_type_generator_ =
        components().addComponentOfType<rnd::RandomNumbersComponent>();
    LogAsserter::log_assert(p_->token_type_generator_ != nullptr,
                            "Cannot create RandomNumbersComponent");

    p_->token_position_generator_ = p_->token_type_generator_;
    LogAsserter::log_assert(p_->token_position_generator_ != nullptr,
                            "Cannot create RandomNumbersComponent");

    auto game_scene_input = components().addComponentOfType<GameSceneInput>();
    game_scene_input->configure(m_sceneStates, m_boardGroup);

    p_->key_mapping_ = muptr<KeyMapping>();
    p_->key_mapping_->reset();

    dataWrapper<sys::FileSerializer>()->deserializeFromFile("keys.txt",
                                                            *p_->key_mapping_);
    dataWrapper<sys::FileSerializer>()->serializeToFile("keys.txt",
                                                        *p_->key_mapping_);

    m_sceneStates->start(GameSceneStates::Playing);
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
    ScoreIncrementer score_incrementer{level_properties_};

    PlayerLauncher player_launcher;
    player_launcher(score_incrementer, *m_boardGroup,
                    [this](vector2df const& v) {
                        p_->createScoreIncrementPoints(*this, v);
                    });
}

void GameScene::tokenHitAnimation(vector2dst const& pos)
{
    auto const lastTokenPosition = m_boardGroup->board2Scene(pos);
    p_->createScoreIncrementPoints(*this, lastTokenPosition);
}

}  // namespace zoper
