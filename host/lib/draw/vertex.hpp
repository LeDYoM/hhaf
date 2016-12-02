#ifndef LIB_DRAW_VERTEX_HPP
#define LIB_DRAW_VERTEX_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/draw/color.hpp>

namespace lib
{
	namespace draw
	{
		class Vertex
		{
		public:
			Vertex() : position{ 0, 0 }, color{ 255, 255, 255 }, texCoords{ 0, 0 } {}
			Vertex(const vector2df &thePosition) : Vertex{ thePosition,{ 255, 255, 255 },{ 0, 0 } } {}
			Vertex(const vector2df &thePosition, const Color &theColor) : Vertex{ thePosition,{ theColor },{ 0, 0 } } {}
			Vertex(const vector2df &thePosition, const vector2df &theTexCoords) : Vertex{ thePosition,{ 255, 255, 255 },{ theTexCoords } } {}
			Vertex(const vector2df &thePosition, const Color &theColor, const vector2df &theTexCoords) : position{ thePosition }, color{ theColor }, texCoords{ theTexCoords } {}

			vector2df position;
			Color color;
			vector2df texCoords;
		};
	}
}

#endif
