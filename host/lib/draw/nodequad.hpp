#ifndef LIB_DRAW_NODEQUAD_HPP__
#define LIB_DRAW_NODEQUAD_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "color.hpp"
#include "renderizable.hpp"

namespace lib
{
	namespace draw
	{
		class Texture;
		class NodeQuad : public Renderizable
		{
		public:
			explicit NodeQuad(const std::string &name, const vector2df& size);
			virtual ~NodeQuad() = default;
			void setSize(const vector2df size);
			u32 getPointCount() const noexcept { return 4; }
			void setTexture(sptr<Texture> texture);

			void setTextureRect(const Rects32& rect);
			Rects32 getTextureRect() const;

		protected:
			void updateGeometry();
			void updateTexCoords();

		private:
			vector2df m_size;
			Rects32 m_textureRect;
		};
	}
}

#endif
