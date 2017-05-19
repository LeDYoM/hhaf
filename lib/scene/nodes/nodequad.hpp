#ifndef LIB_DRAW_NODEQUAD_HPP__
#define LIB_DRAW_NODEQUAD_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
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
				void configureBase();
				virtual void updateGeometrySimpleNode() override;
			};
		}
	}
}

#endif
