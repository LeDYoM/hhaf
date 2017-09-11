#pragma once

#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP__
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scene.hpp>

namespace zoper
{
	class HighScoresScene final : public lib::scene::Scene
	{
	public:
		HighScoresScene();
		virtual ~HighScoresScene() = default;

		// Inherited via Scene
		virtual void create() override;
		virtual void onDeinit() override;

		virtual void updateScene() override;

	private:
	};
}

#endif