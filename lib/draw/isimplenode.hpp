#ifndef LIB_DRAW_ISIMPLENODE_HPP__
#define LIB_DRAW_ISIMPLENODE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "color.hpp"
#include "renderizable.hpp"

namespace lib
{
	namespace draw
	{
		class Texture;
		class ISimpleNode : public Renderizable
		{
		public:
			ISimpleNode(const std::string &name, const vector2df &size, sptr<Texture> texture, const u32 pointCount, const Color &color);
			virtual ~ISimpleNode() = default;

			Property<vector2df> size;
			Property<Rects32> textureRect;

		protected:
			void updateGeometry();
			void updateTextureCoords();

			virtual void updateGeometrySimpleNode() = 0;
		};
	}
}

#endif
