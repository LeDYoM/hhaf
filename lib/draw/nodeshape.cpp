#include "nodeshape.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace draw
	{
		NodeShape::NodeShape(const std::string &name, const vector2df& size, sptr<Texture> texture, const u32 pointCount_, const Color &color)
			: ISimpleNode{ name, size, texture, pointCount_, color }, pointCount{ pointCount_ }
		{
			logConstruct("Name: ", name);

			updateGeometry();
		}

		NodeShape::~NodeShape()
		{
			logDestruct("Name: ", name());
		}

		template <typename T>
		constexpr T PIConstant = 3.14159265358979323846;
		template <typename T>
		constexpr T PID2Constant = 3.14159265358979323846 / static_cast<T>(2);

		void NodeShape::updateGeometrySimpleNode()
		{
			const u32 nPoints(pointCount());
			const u32 nVertex(nPoints + 2);

			BasicVertexArray &vertices(m_vertices.verticesArray());

			vertices.resize(nVertex); // + 2 for center and repeated first point
			const vector2df radius{ size() / 2.0f };
			const f64 baseAngle((2 * PIConstant<f64>) / nPoints);
			for (std::size_t i = 0; i < nPoints; ++i)
			{
				const f64 angle = (i*baseAngle) - (PID2Constant<f64>);
				const vector2dd r{ std::cos(angle) * radius.x, std::sin(angle) * radius.y };
				vertices[i + 1].position = { static_cast<f32>(radius.x + r.x), static_cast<f32>(radius.y + r.y) };
			}

			vertices[nPoints + 1].position = vertices[1].position;

			vertices[0].position = { size().x / 2, size().y / 2 };

			// Update the bounding rectangle
			m_vertices.setBounds({ 0, 0, size().x, size().y });
		}
	}
}
