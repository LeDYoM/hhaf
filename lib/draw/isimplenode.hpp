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
			inline u32 pointCount() const noexcept { return m_pointCount; }

			void setTextureRect(const Rects32& rect);
			Rects32 getTextureRect() const;

			ReadOnlyProperty<Rectf32> bounds;
			TriggerProperty<vector2df> size;
		protected:
			void updateGeometry();
			void updateTexCoords();
			virtual void updateGeometrySimpleNode() = 0;

		protected:
			u32 m_pointCount;
			Rects32 m_textureRect;
		};
	}
}

#endif
