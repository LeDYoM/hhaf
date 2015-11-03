#include "ellipseshape.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			EllipseShape::EllipseShape(const sf::Vector2f& radius) : m_radius{ radius }
			{
				update();
			}

			void EllipseShape::setRadius(const sf::Vector2f& radius)
			{
				m_radius = radius;
				update();
			}

			void EllipseShape::setSize(const sf::Vector2f & size)
			{
				m_radius = size / 2.0f;
				update();
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
				return 30; // fixed, but could be an attribute of the class if needed
			}

			sf::Vector2f EllipseShape::getPoint(unsigned int index) const
			{
				static const float pi = 3.141592654f;

				float angle = index * 2 * pi / getPointCount() - pi / 2;
				float x = std::cos(angle) * m_radius.x;
				float y = std::sin(angle) * m_radius.y;

				return sf::Vector2f(m_radius.x + x, m_radius.y + y);
			}
		}
	}
}
