#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include "../../types.hpp"
#include <SFML/Graphics.hpp>
#include "iscenenode.hpp"

using namespace sf;

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class NodeShape : public Renderizable
			{
			public:
				enum class NodeMode : u8
				{
					Shape = 0,
					Sprite = 1,
				} _mode{ NodeMode::Shape };
				explicit NodeShape(const vector2df& size, const u32 pointCount=4,const NodeMode mode=NodeMode::Shape);
				virtual ~NodeShape();
				void setSize(const sf::Vector2f &size);
				void setSize(const float size);
				const sf::Vector2f &getRadius() const;
				const sf::Vector2f &getSize() const;
				u32 getPointCount() const;
				void setPointCount(lib::u32 numPoints);
				virtual sf::Vector2f getPoint(lib::u32 index) const;
				void setTexture(const sf::Texture *texture, bool resetSize=true, bool resetRect = false);

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

			protected:
				void update();
				void setTexture_(const Texture* texture, bool resetRect = false);
				virtual u32 draw(lib::core::Window *window, sf::RenderStates &states) override;
				void updateFillColors();
				void updateTexCoords();
				void updateOutline();
				void updateOutlineColors();

			private:
				const Texture* m_texture;
				sf::Vector2f _size;
				lib::u32 m_pointCount;
				IntRect m_textureRect;
				Color m_fillColor;
				Color m_outlineColor;
				float m_outlineThickness;
				VertexArray m_vertices;
				VertexArray m_outlineVertices;
				FloatRect m_insideBounds;
				FloatRect m_bounds;
			};
		}
	}
}

#endif
