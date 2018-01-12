#pragma once

#ifndef ZOPER_HIGHSCORES_SCENE_STATES_INCLUDE_HPP__
#define ZOPER_HIGHSCORES_SCENE_STATES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>

namespace zoper
{
	enum class HighScoresSceneStates : lib::u32
	{
		FadeIn	= 0,
		Show	= 1,
		FadeOut	= 2
	};
}

#endif