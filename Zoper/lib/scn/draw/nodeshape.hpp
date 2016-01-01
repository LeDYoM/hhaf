#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include "../../types.hpp"
#include <SFML/Graphics/Shape.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class NodeShape : public sf::Shape
			{
			public:
				explicit NodeShape(const sf::Vector2f& radius, const u32 pointCount);
				void setRadius(const sf::Vector2f & radius);
				void setSize(const sf::Vector2f &size);
				void setRadius(const float radius);
				void setSize(const float size);
				const sf::Vector2f &getRadius() const;
				const sf::Vector2f &getSize() const;
				virtual u32 getPointCount() const override;
				void setPointCount(lib::u32 numPoints);
				virtual sf::Vector2f getPoint(lib::u32 index) const;
				void setTexture(const sf::Texture *texture, bool resetSize=true, bool resetRect = false);
				void setStartAngle(double st);

			private:
				sf::Vector2f m_radius;
				lib::u32 m_pointCount;
				double _startAngle;
			};
		}
	}
}

#endif
