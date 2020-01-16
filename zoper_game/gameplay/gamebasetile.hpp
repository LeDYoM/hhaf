#pragma once

#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizable.hpp>
#include <boardmanager/include/itile.hpp>

namespace zoper
{
    using namespace lib;

    class GameBaseTile : public board::ITile, public scene::SceneNode
    {
    public:
        GameBaseTile(scene::SceneNode* const parent, str name);
        ~GameBaseTile() override;

        void update() override;
        scene::Color getColorForToken() const;

    protected:
        sptr<scene::Renderizable> m_node;
    };
}

#endif