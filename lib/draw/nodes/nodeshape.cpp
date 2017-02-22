#include "nodeshape.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace draw
	{
		namespace nodes
		{
			NodeShape::NodeShape(str_const &&name, const u32 pointCount_)
				: ISimpleNode{ std::move(name), pointCount_ }, pointCount{ pointCount_ }
			{
				logConstruct("Name: ", name);
			}

			NodeShape::~NodeShape()
			{
				logDestruct("Name: ", name());
			}

			void NodeShape::configure()
			{
				ISimpleNode::configure();
			}

			template <typename T>
			constexpr T PIConstant = 3.14159265358979323846;
			template <typename T>
			constexpr T PID2Constant = 3.14159265358979323846 / static_cast<T>(2);

			void NodeShape::updateGeometrySimpleNode()
			{
				const u32 nPoints(pointCount());
				const u32 nVertex(nPoints + 2);

				const Rectf32 &cBox{ box() };
				const vector2df size{ cBox.size() };

				BasicVertexArray &vertices(m_vertices.verticesArray());
				const vector2df radius{ size / 2.0f };

				vertices.resize(nVertex); // + 2 for center and repeated first point
				const f64 baseAngle((2 * PIConstant<f64>) / nPoints);
				for (std::size_t i = 0; i < nPoints; ++i)
				{
					const f64 angle = (i*baseAngle) - (PID2Constant<f64>);
					const vector2dd r{ std::cos(angle) * radius.x, std::sin(angle) * radius.y };
					vertices[i + 1].position = { static_cast<f32>(radius.x + r.x), static_cast<f32>(radius.y + r.y) };
					vertices[i + 1].position += cBox.leftTop();
				}

				vertices[nPoints + 1].position = vertices[1].position;

				vertices[0].position = { size.x / 2, size.y / 2 };
				vertices[0].position += cBox.leftTop();

				// Update the bounding rectangle
				m_vertices.setBounds(cBox);
			}
		}
	}
}
