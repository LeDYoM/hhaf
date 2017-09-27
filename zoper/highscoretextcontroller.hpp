#pragma once

#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/ttfont.hpp>
#include <lib/scene/nodes/theme.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

#include "loaders/highscoresresources.hpp"
#include "highscoresdata.hpp"

namespace zoper
{
	using namespace lib;

	class HighScoreTextController : public scene::SceneNode
	{
	public:
		using ParentClassType = scene::SceneNode;
		HighScoreTextController(scene::SceneNode *parent, sptr<scene::nodes::Theme> theme);
		virtual ~HighScoreTextController();

		virtual void create() override;

	private:
		array<sptr<scene::nodes::NodeText>,10> m_textGroup;
		sptr<scene::nodes::Theme> m_theme;
	};
}

#endif