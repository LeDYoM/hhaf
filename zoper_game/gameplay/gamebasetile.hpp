#pragma once

#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/board/itile.hpp>

namespace zoper
{
    using namespace lib;

	class GameBaseTile : public board::ITile, public scene::SceneNode
	{
	public:
		GameBaseTile(scene::SceneNode* const parent, str name);
		~GameBaseTile() override;

		scene::Color getColorForToken() const;

	protected:
		sptr<scene::Renderizable> m_node;
	};
}

#endif