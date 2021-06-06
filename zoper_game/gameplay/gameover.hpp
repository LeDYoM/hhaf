#ifndef ZOPER_GAMEOVER_SCENENODE_INCLUDE_HPP
#define ZOPER_GAMEOVER_SCENENODE_INCLUDE_HPP

#include <haf/include/scene/scenenode.hpp>

namespace zoper
{
    using namespace haf;

	class GameOverSceneNode : public scene::SceneNode
	{
	public:
        GameOverSceneNode(scene::SceneNode* const parent, htps::str name);
        ~GameOverSceneNode() override;

	private:
        htps::sptr<scene::SceneNode> m_gameOverrg;
    };
}

#endif