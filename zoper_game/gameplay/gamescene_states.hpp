#ifndef ZOOPER_GAMESCENE_STATES_INCLUDE_HPP
#define ZOOPER_GAMESCENE_STATES_INCLUDE_HPP

namespace zoper
{

#include <htypes/include/str.hpp>

enum class GameSceneStates :  htps::u8
{
    Playing = 0U,
    GameOver,
    Pause
};

constexpr const auto make_str(const GameSceneStates gss)
{
    switch (gss)
    {
        case GameSceneStates::Playing:
            return "Playing";
            break;
        case GameSceneStates::GameOver:
            return "GameOver";
            break;
        case GameSceneStates::Pause:
            return "Pause";
            break;
        default:
            return "Invalid GameSceneStates";
    }
}

} // namespace zoper

#endif
