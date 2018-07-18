#pragma once

#ifndef LIB_SCENE_NODEQUAD_INCLUDE_HPP__
#define LIB_SCENE_NODEQUAD_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/renderizable.hpp>

namespace lib::scene::nodes
{
    class NodeQuad : public Renderizable
	{
	public:
        NodeQuad(SceneNode *const parent, const str &name)
            : Renderizable{ parent, name, 4 + 2 } {}
		virtual ~NodeQuad() = default;

	protected:
		virtual void updateGeometrySimpleNode() override;
	};
}

#endif
