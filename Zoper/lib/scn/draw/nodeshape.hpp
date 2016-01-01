#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include "../../types.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class NodeShape : public sf::Drawable, public sf::Transformable
			{
			public:
				explicit NodeShape(const sf::Vector2f& size, const u32 pointCount);
				virtual ~NodeShape();
				void setSize(const sf::Vector2f &size);
				void setSize(const float size);
				const sf::Vector2f &getRadius() const;
				const sf::Vector2f &getSize() const;
				u32 getPointCount() const;
				void setPointCount(lib::u32 numPoints);
				virtual sf::Vector2f getPoint(lib::u32 index) const;
				void setTexture(const sf::Texture *texture, bool resetSize=true, bool resetRect = false);

				void setTexture_(const Texture* texture, bool resetRect = false);
				void setTextureRect(const IntRect& rect);
				void setFillColor(const Color& color);
				void setOutlineColor(const Color& color);
				void setOutlineThickness(float thickness);
				const Texture* getTexture() const;
				const IntRect& getTextureRect() const;
				const Color& getFillColor() const;
				const Color& getOutlineColor() const;
				float getOutlineThickness() const;
				FloatRect getLocalBounds() const;
				FloatRect getGlobalBounds() const;

			private:
				sf::Vector2f _size;
				lib::u32 m_pointCount;
			protected:
				void update();
			private:
				virtual void draw(RenderTarget& target, RenderStates states) const;
				void updateFillColors();
				void updateTexCoords();
				void updateOutline();
				void updateOutlineColors();

			private:
				const Texture* m_texture;          ///< Texture of the shape
				IntRect        m_textureRect;      ///< Rectangle defining the area of the source texture to display
				Color          m_fillColor;        ///< Fill color
				Color          m_outlineColor;     ///< Outline color
				float          m_outlineThickness; ///< Thickness of the shape's outline
				VertexArray    m_vertices;         ///< Vertex array containing the fill geometry
				VertexArray    m_outlineVertices;  ///< Vertex array containing the outline geometry
				FloatRect      m_insideBounds;     ///< Bounding rectangle of the inside (fill)
				FloatRect      m_bounds;           ///< Bounding rectangle of the whole shape (outline + fill)

			};
		}
	}
}

#endif
