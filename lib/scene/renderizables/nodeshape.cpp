#include "nodeshape.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/texture.hpp>

#include <cmath>

namespace lib::scene::nodes
{
	template <typename T>
	constexpr T PiConstant = 3.14159265358979323846;
	template <typename T>
	constexpr T PiD2Constant = PiConstant<T> / static_cast<T>(2);

	void NodeShape::updateGeometrySimpleNode()
	{
		if (pointCount()) {
			const u32 nPoints(pointCount());
			const u32 nVertex(nPoints + 2);

			const vector2df size{ box().size() };

			BasicVertexArray &vertices(m_vertices.verticesArray());
			const vector2df radius{ size / 2.0f };

			vertices.resize(nVertex); // + 2 for center and repeated first point
			const f64 baseAngle((2 * PiConstant<f64>) / static_cast<f64>(nPoints));
			const auto leftTop(box().leftTop());
			for (u32 i{ 0 }; i < nPoints; ++i) {
				const f64 angle{ (i*baseAngle) - (PiD2Constant<f64>) };
				const vector2dd r{ std::cos(angle) * radius.x, std::sin(angle) * radius.y };
				vertices[i + 1].position = { static_cast<f32>(radius.x + r.x), static_cast<f32>(radius.y + r.y) };
				vertices[i + 1].position += leftTop;
			}

			vertices[nPoints + 1].position = vertices[1].position;
			vertices[0].position = (box().size() / 2) + leftTop;

			// Update the bounding rectangle
			m_vertices.bounds = box();
		}
	}
}
