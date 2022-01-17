#ifndef ZOPER_HIGHSCORES_SCENE_STATES_INCLUDE_HPP
#define ZOPER_HIGHSCORES_SCENE_STATES_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace zoper
{
enum class HighScoresSceneStates : htps::u32
{
    FadeIn  = 0,
    Show    = 1,
    FadeOut = 2
};
}

#endif