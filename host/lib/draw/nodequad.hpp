#ifndef LIB_DRAW_NODEQUAD_HPP__
#define LIB_DRAW_NODEQUAD_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "isimplenode.hpp"

namespace lib
{
	namespace draw
	{
		class NodeQuad : public ISimpleNode
		{
		public:
			explicit NodeQuad(const std::string &name, const vector2df& size);
			virtual ~NodeQuad() = default;

		protected:
			virtual void updateGeometrySimpleNode() override;
		};
	}
}

#endif
