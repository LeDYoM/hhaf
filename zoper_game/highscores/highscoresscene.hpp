#pragma once

#ifndef ZOPER_HIGHSCORESSCENE_INCLUDE_HPP__
#define ZOPER_HIGHSCORESSCENE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

#include <lib/scene/scene.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/ttfont.hpp>

#include <lib/include/scene/iscene.hpp>

namespace zoper
{
    using namespace lib;
    class HighScoreTextController;
	class HighScoresScene final : public scene::Scene
	{
	public:

		DECLARE_SCENE(HighScoresScene)

		HighScoresScene();
		~HighScoresScene() override;

		void onCreated() override;
		void updateScene() override;

	private:
        using BaseClass = lib::scene::Scene;

		sptr<scene::nodes::NodeQuad> m_background;
		sptr<HighScoreTextController> m_highScoreTextController;
        sptr<scene::Font> m_normalFont;
		scene::Color m_normalColor;
		scene::Color m_selectedColor;
		ireceiver m_receiver;
	};
}

#endif
