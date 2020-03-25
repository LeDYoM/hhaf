#pragma once

#ifndef ZOPER_BOARDSCENENODE_INCLUDE_HPP
#define ZOPER_BOARDSCENENODE_INCLUDE_HPP

#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/color.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <lib/scene/include/scenenodetypes.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;

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