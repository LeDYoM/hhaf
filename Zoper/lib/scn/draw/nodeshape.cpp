#include "NodeShape.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "../../log.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			NodeShape::NodeShape(const vector2df& size, const u32 pointCount, const NodeMode mode)
				: _mode{ mode },
				m_texture{ nullptr },m_textureRect(),m_fillColor(255, 255, 255),
				m_outlineColor(255, 255, 255),m_outlineThickness(0),m_vertices(TrianglesFan),
				m_outlineVertices(TrianglesStrip),m_insideBounds(),
				m_bounds(), _size{ size }, m_pointCount{ pointCount }
			{
				update();
			}

			NodeShape::~NodeShape()
			{

			}

			void NodeShape::setSize(const sf::Vector2f & size)
			{
				_size = size;
				update();
			}

			void NodeShape::setSize(const float size)
			{
				setSize(sf::Vector2f(size,size));
			}

			const sf::Vector2f& NodeShape::getRadius() const
			{
				return _size / 2.0f;
			}

			const sf::Vector2f & NodeShape::getSize() const
			{
				return _size;
			}

			u32 NodeShape::getPointCount() const
			{
				return m_pointCount;
			}

			void NodeShape::setPointCount(lib::u32 numPoints)
			{
				m_pointCount = numPoints;
				update();
			}
			
			vector2df NodeShape::getPoint(unsigned int index) const
			{
				// TO DO:
				// Optimize and cache it
				switch (_mode)
				{
				default:
				case lib::scn::draw::NodeShape::NodeMode::Shape:
				{
					sf::Vector2f m_radius{ _size / 2.0f };
					double angle = ((index * 2 * M_PI) / getPointCount()) - (M_PI_2);
					double x = std::cos(angle) * m_radius.x;
					double y = std::sin(angle) * m_radius.y;

					return vector2df(static_cast<float>(m_radius.x + x), static_cast<float>(m_radius.y + y));

				}
				break;
				case lib::scn::draw::NodeShape::NodeMode::Sprite:
				{
					__ASSERT(m_pointCount == 4, "Invalid sprite state");

					switch (index)
					{
					default:
					case 0: return vector2df(0, 0);
					case 1: return vector2df(_size.x, 0);
					case 2: return vector2df(_size.x, _size.y);
					case 3: return vector2df(0, _size.y);
					}
				}
				break;
				}
			}

			void NodeShape::setTexture(const sf::Texture *texture, bool resetSize/*=true*/, bool resetRect /*= false*/)
			{
				setTexture_(texture, resetRect);
				if (resetSize)
				{
					setSize(static_cast<sf::Vector2f>(texture->getSize()));
				}
			}

			// Compute the normal of a segment
			vector2df computeNormal(const ::sf::Vector2f& p1, const sf::Vector2f& p2)
			{
				::sf::Vector2f normal(p1.y - p2.y, p2.x - p1.x);
				float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
				if (length != 0.f)
					normal /= length;
				return normal;
			}

			// Compute the dot product of two vectors
			float dotProduct(const vector2df& p1, const vector2df& p2)
			{
				return p1.x * p2.x + p1.y * p2.y;
			}

			void NodeShape::setTexture_(const Texture* texture, bool resetRect)
			{
				if (texture)
				{
					// Recompute the texture area if requested, or if there was no texture & rect before
					if (resetRect || (!m_texture && (m_textureRect == IntRect())))
						setTextureRect(IntRect(0, 0, texture->getSize().x, texture->getSize().y));
				}

				// Assign the new texture
				m_texture = texture;
			}


			const Texture* NodeShape::getTexture() const
			{
				return m_texture;
			}

			void NodeShape::setTextureRect(const IntRect& rect)
			{
				m_textureRect = rect;
				updateTexCoords();
			}

			const IntRect& NodeShape::getTextureRect() const
			{
				return m_textureRect;
			}

			void NodeShape::setFillColor(const Color& color)
			{
				m_fillColor = color;
				updateFillColors();
			}

			const Color& NodeShape::getFillColor() const
			{
				return m_fillColor;
			}

			void NodeShape::setOutlineColor(const Color& color)
			{
				m_outlineColor = color;
				updateOutlineColors();
			}

			const Color& NodeShape::getOutlineColor() const
			{
				return m_outlineColor;
			}

			void NodeShape::setOutlineThickness(float thickness)
			{
				m_outlineThickness = thickness;
				update(); // recompute everything because the whole shape must be offset
			}

			float NodeShape::getOutlineThickness() const
			{
				return m_outlineThickness;
			}

			FloatRect NodeShape::getLocalBounds() const
			{
				return m_bounds;
			}

			FloatRect NodeShape::getGlobalBounds() const
			{
				return getTransform().transformRect(getLocalBounds());
			}

			void NodeShape::update()
			{
				// Get the total number of points of the shape
				std::size_t count = getPointCount();
				if (count < 3)
				{
					m_vertices.resize(0);
					m_outlineVertices.resize(0);
					return;
				}

				m_vertices.resize(count + 2); // + 2 for center and repeated first point

				// Position
				for (std::size_t i = 0; i < count; ++i)
					m_vertices[i + 1].position = getPoint(i);
				m_vertices[count + 1].position = m_vertices[1].position;

				// Update the bounding rectangle
				m_vertices[0] = m_vertices[1]; // so that the result of getBounds() is correct
				m_insideBounds = m_vertices.getBounds();

				// Compute the center and make it the first vertex
				m_vertices[0].position.x = m_insideBounds.left + m_insideBounds.width / 2;
				m_vertices[0].position.y = m_insideBounds.top + m_insideBounds.height / 2;

				// Color
				updateFillColors();

				// Texture coordinates
				updateTexCoords();

				// Outline
				updateOutline();
			}

			void NodeShape::draw(RenderTarget& target, RenderStates states) const
			{
				states.transform *= getTransform();

				// Render the inside
				states.texture = m_texture;
				target.draw(m_vertices, states);

				// Render the outline
				if (m_outlineThickness != 0)
				{
					states.texture = NULL;
					target.draw(m_outlineVertices, states);
				}
			}

			void NodeShape::updateFillColors()
			{
				for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
					m_vertices[i].color = m_fillColor;
			}

			void NodeShape::updateTexCoords()
			{
				for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
				{
					float xratio = m_insideBounds.width > 0 ? (m_vertices[i].position.x - m_insideBounds.left) / m_insideBounds.width : 0;
					float yratio = m_insideBounds.height > 0 ? (m_vertices[i].position.y - m_insideBounds.top) / m_insideBounds.height : 0;
					m_vertices[i].texCoords.x = m_textureRect.left + m_textureRect.width * xratio;
					m_vertices[i].texCoords.y = m_textureRect.top + m_textureRect.height * yratio;
				}
			}

			void NodeShape::updateOutline()
			{
				std::size_t count = m_vertices.getVertexCount() - 2;
				m_outlineVertices.resize((count + 1) * 2);

				for (std::size_t i = 0; i < count; ++i)
				{
					std::size_t index = i + 1;

					// Get the two segments shared by the current point
					Vector2f p0 = (i == 0) ? m_vertices[count].position : m_vertices[index - 1].position;
					Vector2f p1 = m_vertices[index].position;
					Vector2f p2 = m_vertices[index + 1].position;

					// Compute their normal
					Vector2f n1 = computeNormal(p0, p1);
					Vector2f n2 = computeNormal(p1, p2);

					// Make sure that the normals point towards the outside of the shape
					// (this depends on the order in which the points were defined)
					if (dotProduct(n1, m_vertices[0].position - p1) > 0)
						n1 = -n1;
					if (dotProduct(n2, m_vertices[0].position - p1) > 0)
						n2 = -n2;

					// Combine them to get the extrusion direction
					float factor = 1.f + (n1.x * n2.x + n1.y * n2.y);
					Vector2f normal = (n1 + n2) / factor;

					// Update the outline points
					m_outlineVertices[i * 2 + 0].position = p1;
					m_outlineVertices[i * 2 + 1].position = p1 + normal * m_outlineThickness;
				}

				// Duplicate the first point at the end, to close the outline
				m_outlineVertices[count * 2 + 0].position = m_outlineVertices[0].position;
				m_outlineVertices[count * 2 + 1].position = m_outlineVertices[1].position;

				// Update outline colors
				updateOutlineColors();

				// Update the shape's bounds
				m_bounds = m_outlineVertices.getBounds();
			}

			void NodeShape::updateOutlineColors()
			{
				for (std::size_t i = 0; i < m_outlineVertices.getVertexCount(); ++i)
					m_outlineVertices[i].color = m_outlineColor;
			}

		}
	}
}
