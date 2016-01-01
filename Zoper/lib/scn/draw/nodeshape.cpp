#include "NodeShape.hpp"
#include <SFML/Graphics/Texture.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			NodeShape::NodeShape(const sf::Vector2f& radius, const u32 pointCount)
				: m_radius{ radius }, m_pointCount{ pointCount }
			{
//				setStartAngle(M_PI / 4);
				setStartAngle(M_PI_2);
			}

			void NodeShape::setStartAngle(double st)
			{
				_startAngle = st;
				update();
			}

			void NodeShape::setRadius(const sf::Vector2f& radius)
			{
				m_radius = radius;
				update();
			}

			void NodeShape::setRadius(const float radius)
			{
				setRadius(sf::Vector2f(radius, radius));
			}

			void NodeShape::setSize(const sf::Vector2f & size)
			{
				m_radius = size / 2.0f;
				update();
			}

			void NodeShape::setSize(const float size)
			{
				setSize(sf::Vector2f(size,size));
			}

			const sf::Vector2f& NodeShape::getRadius() const
			{
				return m_radius;
			}

			const sf::Vector2f & NodeShape::getSize() const
			{
				return m_radius * 2.0f;
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

			sf::Vector2f NodeShape::getPoint(unsigned int index) const
			{
				// TO DO:
				// Optimize and cache it

				double angle = ((index * 2 * M_PI) / getPointCount()) - (_startAngle);
				double x = std::cos(angle) * m_radius.x;
				double y = std::sin(angle) * m_radius.y;

				return sf::Vector2f(static_cast<float>(m_radius.x + x), static_cast<float>(m_radius.y + y));
			}

			void NodeShape::setTexture(const sf::Texture *texture, bool resetSize/*=true*/, bool resetRect /*= false*/)
			{
				sf::Shape::setTexture(texture, resetRect);
				if (resetSize)
				{
					setSize(static_cast<sf::Vector2f>(texture->getSize()));
				}
			}
		}
	}
}
