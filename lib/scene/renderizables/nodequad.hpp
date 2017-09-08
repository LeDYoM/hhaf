#pragma once

#ifndef LIB_DRAW_NODEQUAD_HPP__
#define LIB_DRAW_NODEQUAD_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include "isimplenode.hpp"

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			class NodeQuad : public ISimpleNode
			{
			public:
				explicit NodeQuad(SceneNode *const parent, const str &name) : ISimpleNode{ parent, name, 4 } {}
				virtual ~NodeQuad() = default;

			protected:
				virtual void updateGeometrySimpleNode() override;
			};
		}
	}
}

#endif
