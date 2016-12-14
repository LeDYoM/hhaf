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
			ISimpleNode(const std::string &name, const vector2df &size, const u32 pointCount);
			virtual ~ISimpleNode() = default;
			virtual void setSize(const vector2df size);
			vector2df size() const noexcept { return m_size; }
			u32 getPointCount() const noexcept { return m_pointCount; }
			void setTexture(sptr<Texture> texture);

			void setTextureRect(const Rects32& rect);
			Rects32 getTextureRect() const;

		protected:
			void updateGeometry();
			void updateTexCoords();
			virtual void updateGeometrySimpleNode() = 0;

		protected:
			vector2df m_size;
			u32 m_pointCount;
			Rects32 m_textureRect;
		};
	}
}

#endif
