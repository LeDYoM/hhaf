#ifndef LIB_DRAW_NODEQUAD_HPP__
#define LIB_DRAW_NODEQUAD_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "isimplenode.hpp"

namespace lib
{
	namespace draw
	{
		namespace nodes
		{
			class NodeQuad : public ISimpleNode
			{
			public:
				explicit NodeQuad(const str_const name);
				virtual ~NodeQuad();

				virtual void configure() override;

			protected:
				virtual void updateGeometrySimpleNode() override;
			};
		}
	}
}

#endif
