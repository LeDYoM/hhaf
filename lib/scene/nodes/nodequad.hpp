#ifndef LIB_DRAW_NODEQUAD_HPP__
#define LIB_DRAW_NODEQUAD_HPP__

#pragma once

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
				explicit NodeQuad(str&& name);
				virtual ~NodeQuad();

				virtual void configure() override;

			protected:
				virtual void updateGeometrySimpleNode() override;
			};
		}
	}
}

#endif
