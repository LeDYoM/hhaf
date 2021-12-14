#include "levelproperties.hpp"
#include "../gameshareddata.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/shareddata/shareddataupdater.hpp>
#include <haf/include/system/datawrappercreator.hpp>
#include <haf/include/time/timercomponent.hpp>

using namespace htps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::sys;

void LevelProperties::configure(
    size_type const currentLevel,
    GameMode const gameMode,
    sptr<time::TimerComponent> scene_timer_component)
{
    using namespace time;

    LogAsserter::log_assert(scene_timer_component != nullptr,
                            "Passed nullptr sceneTimerComponent");
    LogAsserter::log_assert(scene_timer_component_ == nullptr,
                            "m_sceneNodeComponent already contains a value");

    game_mode_             = gameMode;
    scene_timer_component_ = std::move(scene_timer_component);

    LogAsserter::log_assert(level_timer_ == nullptr,
                            "LevelProperties already has a timer!");
    level_timer_ = scene_timer_component_->addFreeTimer();

    update_level_data_timer_ = scene_timer_component_->addTimer(
        TimerType::Continuous, TimePoint_as_miliseconds(120U),
        [this](TimePoint /*realEllapsed*/) { updateLevelData(); });

    game_hud_ = attachedNode()->createSceneNode<GameHudSceneNode>("hud");

    setScore(0U);
    setLevel(currentLevel);
}

void LevelProperties::setScore(size_type const new_score)
{
    current_score_ = new_score;

    {
        auto const game_shared_data_updater =
            attachedNode()
                ->dataWrapper<shdata::SharedDataUpdater<GameSharedData>>();
        auto game_shared_data =
            game_shared_data_updater->update(GameSharedData::address());

        if (!game_shared_data)
        {
            DisplayLog::debug("Cannot retrieve GameSharedData");
        }
        else
        {
            game_shared_data->score = current_score_;
        }
    }
    game_hud_->setScore(current_score_);
}

htps::size_type LevelProperties::millisBetweenTokens() const
{
    return millis_between_tokens_;
}

void LevelProperties::setLevel(LevelType const currentLevel)
{
    level_timer_->restart();

    current_level_ = currentLevel;

    {
        auto game_shared_data =
            attachedNode()
                ->dataWrapper<shdata::SharedDataUpdater<GameSharedData>>()
                ->update(GameSharedData::address());

        if (game_shared_data == nullptr)
        {
            DisplayLog::debug("Cannot retrieve GameSharedData");
        }

        game_shared_data->endLevel = current_level_;
    }

    base_score_      = 2U * (current_level_ + 1U);
    consumed_tokens_ = 0U;

    if (current_level_ <= maxLevelWithProperties)
    {
        millis_between_tokens_ = 1350U - (current_level_ * 50U);
        stay_counter_ =
            ((game_mode_ == GameMode::Time) ? 180U + (current_level_ * 30U)
                                            : 25U + (10U * current_level_));
    }
    else
    {
        millis_between_tokens_ = 50;
        stay_counter_ = ((game_mode_ == GameMode::Time) ? 1200U : 400U);
    }

    levelChanged(currentLevel);
    updateGoals();
    updateLevelData();
    increaseScore(0U);

    DisplayLog::info("Level set: ", current_level_);
    DisplayLog::info("Millis between tokens: ", millisBetweenTokens());
    DisplayLog::info("Current base score: ", baseScore());
    DisplayLog::info("Seconds or tokens to next level: ", stayCounter());
}

void LevelProperties::tokenConsumed()
{
    ++consumed_tokens_;
    updateLevelData();
}

void LevelProperties::updateGoals()
{
    game_hud_->setLevel(current_level_);
    game_hud_->setStayCounter(stay_counter_);
}

void LevelProperties::updateLevelData()
{
    switch (game_mode_)
    {
        default:
        case GameMode::Token:
            game_hud_->setConsumedTokens(consumed_tokens_);

            if (consumed_tokens_ >= stay_counter_)
            {
                nextLevel();
            }
            break;

        case GameMode::Time:
            game_hud_->setEllapsedTimeInSeconds(
                level_timer_->ellapsed().seconds());

            if (level_timer_->ellapsed().seconds() >= stay_counter_)
            {
                nextLevel();
            }
            break;
    }
}

void LevelProperties::increaseScore(size_type const scoreIncrement)
{
    setScore(current_score_ + scoreIncrement);
}

void LevelProperties::nextLevel()
{
    setLevel(current_level_ + 1);
}

}  // namespace zoper
