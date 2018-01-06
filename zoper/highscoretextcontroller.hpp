#pragma once

#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/ttfont.hpp>
#include <lib/scene/nodes/theme.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/scenenodetypes.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

#include "loaders/highscoresresources.hpp"
#include "highscoresdata.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	class HighScoreTextController : public scene::nodes::TableNode<scene::TextSceneNode>
	{
	private:
		using BaseClass = scene::nodes::TableNode<scene::TextSceneNode>;
	public:
		HighScoreTextController(scene::SceneNode *parent, str name);
		virtual ~HighScoreTextController();

		virtual void onCreated() override;

		emitter<> Finished;

	private:
		void standarizeText(const sptr<nodes::NodeText> &ntext);
		void saveHighScores();
		sptr<TTFont> m_normalFont;
		Color m_normalColor;
		Color m_selectedColor;
		size_type m_normalCharacterSize;
	};
}

#endif