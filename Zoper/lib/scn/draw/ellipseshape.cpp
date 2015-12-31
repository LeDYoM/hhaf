#include "ellipseshape.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			EllipseShape::EllipseShape(const sf::Vector2f& radius) : m_radius{ radius }, m_pointCount{ 30 }
			{
				update();
			}

			void EllipseShape::setRadius(const sf::Vector2f& radius)
			{
				m_radius = radius;
				update();
			}

			void EllipseShape::setRadius(const float radius)
			{
				setRadius(sf::Vector2f(radius, radius));
			}

			void EllipseShape::setSize(const sf::Vector2f & size)
			{
				m_radius = size / 2.0f;
				update();
			}

			void EllipseShape::setSize(const float size)
			{
				setSize(sf::Vector2f(size,size));
			}

			const sf::Vector2f& EllipseShape::getRadius() const
			{
				return m_radius;
			}

			const sf::Vector2f & EllipseShape::getSize() const
			{
				return m_radius * 2.0f;
			}

			u32 EllipseShape::getPointCount() const
			{
				return m_pointCount;
			}

			void EllipseShape::setPointCount(lib::u32 numPoints)
			{
				m_pointCount = numPoints;
				update();
			}

			sf::Vector2f EllipseShape::getPoint(unsigned int index) const
			{
				// TO DO:
				// Optimize and cache it
				static const float pi = 3.141592654f;

				float angle = index * 2 * pi / getPointCount() - pi / 2;
				float x = std::cos(angle) * m_radius.x;
				float y = std::sin(angle) * m_radius.y;

				return sf::Vector2f(m_radius.x + x, m_radius.y + y);
			}
		}
	}
}
