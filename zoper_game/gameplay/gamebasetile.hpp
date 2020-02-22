#pragma once

#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <boardmanager/include/itile.hpp>

namespace zoper
{
namespace mtps = lib;
namespace haf = lib;
namespace scene = haf::scene;

class GameBaseTile : public haf::board::ITile, public haf::scene::SceneNode
{
public:
    GameBaseTile(scene::SceneNode *const parent, mtps::str name);
    ~GameBaseTile() override;

    void update() override;
    scene::Color getColorForToken() const;

protected:
   mtps:: sptr<scene::Renderizable> m_node;
};
} // namespace zoper

#endif