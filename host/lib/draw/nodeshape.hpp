#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "color.hpp"
#include "renderizable.hpp"

namespace lib
{
	namespace draw
	{
		class Texture;
		class NodeShape : public Renderizable
		{
		public:
			enum class NodeMode : u8
			{
				Shape = 0,
				Sprite = 1,
			} _mode{ NodeMode::Shape };
			explicit NodeShape(const std::string &name, const vector2df& size, const u32 pointCount,const NodeMode mode);
			virtual ~NodeShape();
			void setSize(const vector2df size);
			u32 getPointCount() const;
			void setPointCount(const u32 numPoints);
			virtual vector2df getPoint(const u32 index) const;
			void setTexture(sptr<Texture> texture, bool resetSize=true, bool resetRect = false);

			void setTextureRect(const Rects32& rect);
			Rects32 getTextureRect() const;

		protected:
			void updateGeometry();
			void updateTexCoords();

		private:
			vector2df m_size;
			u32 m_pointCount;
			Rects32 m_textureRect;
		};
	}
}

#endif
