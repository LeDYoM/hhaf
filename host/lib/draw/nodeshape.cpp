#include "NodeShape.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/draw/texture.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

namespace lib
{
	namespace draw
	{
		NodeShape::NodeShape(const std::string &name, const vector2df& size, const u32 pointCount, const NodeMode mode)
			: Renderizable{ name, TriangleFan }, _mode{ mode }, m_texture{ nullptr }, m_textureRect{}, m_fillColor{ 255, 255, 255 },
			m_size{ size }, m_pointCount{ pointCount }
		{
			update();
		}

		NodeShape::~NodeShape() = default;

		void NodeShape::setSize(const vector2df & size)
		{
			m_size = size;
			update();
		}

		void NodeShape::setSize(const f32 size)
		{
			setSize({ size,size });
		}

		const vector2df & NodeShape::getSize() const
		{
			return m_size;
		}

		u32 NodeShape::getPointCount() const
		{
			return m_pointCount;
		}

		void NodeShape::setPointCount(const u32 numPoints)
		{
			m_pointCount = numPoints;
			update();
		}
			
		vector2df NodeShape::getPoint(const u32 index) const
		{
			// TO DO:
			// Optimize and cache it
			switch (_mode)
			{
			default:
			case lib::draw::NodeShape::NodeMode::Shape:
			{
				vector2df m_radius{ m_size / 2.0f };
				const f64 angle = ((index * 2 * M_PI) / getPointCount()) - (M_PI_2);
				const vector2dd r{ std::cos(angle) * m_radius.x, std::sin(angle) * m_radius.y };
				return vector2df(static_cast<f32>(m_radius.x + r.x), static_cast<f32>(m_radius.y + r.y));
			}
			break;
			case lib::draw::NodeShape::NodeMode::Sprite:
			{
				__ASSERT(m_pointCount == 4, "Invalid sprite state");

				switch (index)
				{
				default:
				case 0: return vector2df(0, 0);
				case 1: return vector2df(m_size.x, 0);
				case 2: return vector2df(m_size.x, m_size.y);
				case 3: return vector2df(0, m_size.y);
				}
			}
			break;
			}
		}

		void NodeShape::setTexture(sptr<Texture> texture, bool resetSize/*=true*/, bool resetRect /*= false*/)
		{
			if (texture) {
				// Recompute the texture area if requested, or if there was no texture & rect before
				if (resetRect || (!m_texture && m_textureRect == Rects32{})) {
					setTextureRect({ 0, 0, static_cast<s32>(texture->getSize().x), static_cast<s32>(texture->getSize().y) });
				}
			}

			// Assign the new texture
			m_texture = texture;

			if (resetSize) {
				setSize({ static_cast<f32>(texture->getSize().x), static_cast<f32>(texture->getSize().y) });
			}
		}

		// Compute the normal of a segment
		vector2df computeNormal(const vector2df& p1, const vector2df& p2)
		{
			vector2df normal(p1.y - p2.y, p2.x - p1.x);
			f32 length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
			if (length != 0.f)
				normal /= length;
			return normal;
		}

		// Compute the dot product of two vectors
		float dotProduct(const vector2df& p1, const vector2df& p2)
		{
			return p1.x * p2.x + p1.y * p2.y;
		}

		sptr<Texture> NodeShape::getTexture() const
		{
			return m_texture;
		}

		void NodeShape::setTextureRect(const Rects32& rect)
		{
			m_textureRect = rect;
			updateTexCoords();
		}

		Rects32 NodeShape::getTextureRect() const
		{
			return m_textureRect;
		}

		void NodeShape::setColor(const Color color)
		{
			m_fillColor = color;
			updateFillColors();
		}

		Color NodeShape::getFillColor() const
		{
			return m_fillColor;
		}

		void NodeShape::update()
		{
			// Get the total number of points of the shape
			auto count = getPointCount();
			if (count < 3) {
				m_vertices.resize(0);
				return;
			}

			m_vertices.resize(count + 2); // + 2 for center and repeated first point

			// Position
			for (std::size_t i = 0; i < count; ++i)
				m_vertices[i + 1].position = getPoint(i);
		
			m_vertices[count + 1].position = m_vertices[1].position;

			// Update the bounding rectangle
			m_vertices[0] = m_vertices[1]; // so that the result of getBounds() is correct
			m_bounds = m_vertices.getBounds();
			// Compute the center and make it the first vertex
			m_vertices[0].position.x = m_bounds.width / 2;
			m_vertices[0].position.y = m_bounds.height / 2;

			// Color
			updateFillColors();

			// Texture coordinates
			updateTexCoords();
		}

		void NodeShape::draw()
		{
			auto handle = host().rStates().pushChanges(&getTransform(), &(*m_texture));
			m_vertices.draw();
		}

		void NodeShape::updateFillColors()
		{
			m_vertices.for_each_vertex([this](Vertex& v) { v.color = m_fillColor; });
		}

		void NodeShape::updateTexCoords()
		{
			m_vertices.for_each_vertex([this](Vertex& v)
			{
				const f32 xratio = m_bounds.width > 0 ? (v.position.x - m_bounds.left) / m_bounds.width : 0;
				const f32 yratio = m_bounds.height > 0 ? (v.position.y - m_bounds.top) / m_bounds.height : 0;
				v.texCoords.x = m_textureRect.left + m_textureRect.width * xratio;
				v.texCoords.y = m_textureRect.top + m_textureRect.height * yratio;
			});
		}
	}
}
