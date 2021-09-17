#ifndef ZOOPER_GAMESCENE_STATES_INCLUDE_HPP
#define ZOOPER_GAMESCENE_STATES_INCLUDE_HPP

#include <htypes/include/str.hpp>

namespace zoper
{
enum class GameSceneStates : htps::u8
{
    Playing = 0U,
    GameOver,
    Pause
};

constexpr auto const make_str(GameSceneStates const gss) noexcept
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

}  // namespace zoper

#endif
