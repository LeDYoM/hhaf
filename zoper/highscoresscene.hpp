#pragma once

#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP__
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include "mainmenuresources.hpp"

namespace zoper
{
	class HighScoresScene final : public lib::scene::Scene
	{
	public:
		HighScoresScene();
		virtual ~HighScoresScene() = default;

		// Inherited via Scene
		void create() override;
		void onDeinit() override;

		void updateScene() override;

	private:
		template <typename T>
		using sptr = std::shared_ptr<T>;

		sptr<MainMenuResources> mainMenuResources;
		sptr<lib::scene::nodes::NodeQuad> m_background;
	};
}

#endif