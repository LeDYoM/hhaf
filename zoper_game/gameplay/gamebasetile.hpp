#pragma once

#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <boardmanager/include/itile.hpp>

namespace haf::board
{
    class BoardModelComponent;
}
namespace zoper
{

class GameBaseTile : public haf::board::ITile, public haf::scene::SceneNode
{
public:
    GameBaseTile(haf::scene::SceneNode* const parent, mtps::str name);
    ~GameBaseTile() override;

    haf::scene::Color getColorForToken() const;

    void tileChanged(const mtps::vector2dst& /*position */,
                     const haf::board::BoardTileData /* oldValue */,
                     const haf::board::BoardTileData /* newValue */) override;

    mtps::sptr<haf::board::BoardModelComponent> getBoardModel();

protected:
    mtps::sptr<haf::scene::Renderizable> m_node;
};
}  // namespace zoper

#endif