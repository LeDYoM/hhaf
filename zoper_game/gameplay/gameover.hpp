#pragma once

#ifndef ZOPER_GAMEOVER_SCENENODE_INCLUDE_HPP
#define ZOPER_GAMEOVER_SCENENODE_INCLUDE_HPP

#include <lib/scene/include/scenenode.hpp>

namespace zoper
{
    using namespace lib;

	class GameOverSceneNode : public scene::SceneNode
	{
	public:
        GameOverSceneNode(scene::SceneNode* const parent, str name);
        ~GameOverSceneNode() override;

	private:
        sptr<scene::SceneNode> m_gameOverrg;
    };
}

#endif