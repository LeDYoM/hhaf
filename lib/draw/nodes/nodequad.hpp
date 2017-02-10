#ifndef LIB_DRAW_NODEQUAD_HPP__
#define LIB_DRAW_NODEQUAD_HPP__

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
				explicit NodeQuad(const std::string &name, const Rectf32 &box, sptr<Texture> texture, const Color &color);
				virtual ~NodeQuad();

			protected:
				virtual void updateGeometrySimpleNode() override;
			};
		}
	}
}

#endif
