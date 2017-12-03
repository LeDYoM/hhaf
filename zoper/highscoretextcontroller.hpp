#pragma once

#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/ttfont.hpp>
#include <lib/scene/nodes/theme.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/scenenodetypes.hpp>
#include "loaders/highscoresresources.hpp"
#include "highscoresdata.hpp"

namespace zoper
{
	using namespace lib;

	class HighScoreTextController : public scene::nodes::TableNode<TextSceneNode>
	{
	private:
		using BaseClass = scene::nodes::TableNode<TextSceneNode>;
	public:
		HighScoreTextController(scene::SceneNode *parent, str name);
		virtual ~HighScoreTextController();

		virtual void create() override;

	};
}

#endif