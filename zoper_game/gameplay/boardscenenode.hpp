#pragma once

#ifndef ZOPER_BOARDSCENENODE_INCLUDE_HPP
#define ZOPER_BOARDSCENENODE_INCLUDE_HPP

#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/color.hpp>
#include <haf/scene/include/renderizable.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;

class BoardSceneNode : public SceneNode
{
private:
    using BaseClass = SceneNode;

public:
    BoardSceneNode(SceneNode *parent, mtps::str name, const mtps::Rectf32 &tileBox);
    virtual ~BoardSceneNode();

    void setTileColor(Color color);

private:
    mtps::sptr<Renderizable> m_backgroundTile;
    mtps::sptr<RenderizableSceneNode> m_pointInCenter;
};
} // namespace zoper

#endif