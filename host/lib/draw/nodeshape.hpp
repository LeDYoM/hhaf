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
			} m_mode{ NodeMode::Shape };
			explicit NodeShape(const std::string &name, const vector2df& size, const u32 pointCount,const NodeMode mode);
			virtual ~NodeShape();
			void setSize(const vector2df size);
			u32 getPointCount() const noexcept { return m_pointCount; }
			void setPointCount(const u32 numPoints);
			void setTexture(sptr<Texture> texture);

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
