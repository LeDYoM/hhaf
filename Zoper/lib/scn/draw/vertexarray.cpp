#include "vertexarray.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			VertexArray::VertexArray()
				: m_vertices(), m_primitiveType{ sf::Points } {	}

			VertexArray::VertexArray(sf::PrimitiveType type, std::size_t vertexCount)
				: m_vertices( vertexCount ), m_primitiveType{ type } { }

			std::size_t VertexArray::getVertexCount() const
			{
				return m_vertices.size();
			}

			sf::Vertex& VertexArray::operator [](std::size_t index)
			{
				return m_vertices[index];
			}

			const sf::Vertex& VertexArray::operator [](std::size_t index) const
			{
				return m_vertices[index];
			}

			void VertexArray::clear()
			{
				m_vertices.clear();
			}

			void VertexArray::resize(std::size_t vertexCount)
			{
				m_vertices.resize(vertexCount);
			}

			void VertexArray::append(const sf::Vertex& vertex)
			{
				m_vertices.push_back(vertex);
			}

			void VertexArray::setPrimitiveType(sf::PrimitiveType type)
			{
				m_primitiveType = type;
			}

			sf::PrimitiveType VertexArray::getPrimitiveType() const
			{
				return m_primitiveType;
			}

			floatRect VertexArray::getBounds() const
			{
				if (!m_vertices.empty())
				{
					float left = m_vertices[0].position.x;
					float top = m_vertices[0].position.y;
					float right = m_vertices[0].position.x;
					float bottom = m_vertices[0].position.y;

					for (std::size_t i = 1; i < m_vertices.size(); ++i)
					{
						vector2df position = m_vertices[i].position;

						// Update left and right
						if (position.x < left)
							left = position.x;
						else if (position.x > right)
							right = position.x;

						// Update top and bottom
						if (position.y < top)
							top = position.y;
						else if (position.y > bottom)
							bottom = position.y;
					}

					return floatRect(left, top, right - left, bottom - top);
				}
				else
				{
					// Array is empty
					return floatRect();
				}
			}

			void VertexArray::draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				if (!m_vertices.empty())
					target.draw(&m_vertices[0], m_vertices.size(), m_primitiveType, states);
			}
		}
	}
}
