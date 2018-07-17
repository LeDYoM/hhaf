#include "nodeshape.hpp"
#include "geometry_math.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/texture.hpp>

namespace lib::scene::nodes
{
	void NodeShape::updateGeometrySimpleNode()
	{
        if (pointCount()) {
            const Rectf32 &cBox{ box() };
            auto& vertices(m_vertices.verticesArray());

            const size_type nPoints{pointCount()};
            const size_type nVertex{nPoints + 2};

            const vector2df size{ cBox.size() };
            const vector2df radius{ size / 2.0f };

            vertices.resize(nVertex); // + 2 for center and repeated first point
            const f64 baseAngle((2 * PiConstant<f64>) / static_cast<f64>(nPoints));
            const auto leftTop(cBox.leftTop());
            for (u32 i{ 0 }; i < nPoints; ++i) {
                const f64 angle{ (i*baseAngle) - (PiD2Constant<f64>) };

                const vector2dd r{ std::cos(angle) * radius.x,
                            std::sin(angle) * radius.y };

                vertices[i + 1].position = vector2df{
                                           static_cast<f32>(radius.x + r.x),
                                           static_cast<f32>(radius.y + r.y) }
                                           + leftTop;
            }

            vertices[nPoints + 1].position = vertices[1].position;
            vertices[0].position = (cBox.size() / 2) + leftTop;
        }
	}
}
