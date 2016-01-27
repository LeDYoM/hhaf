#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include "../../types.hpp"
#include "scenenode.hpp"
#include "iscenenode.hpp"
#include <SFML/Graphics.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class NodeShape : public SceneNode, public ISceneNode
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

				void setTextureRect(const intRect& rect);
				void setFillColor(const color& color);
				void setOutlineColor(const color& color);
				void setOutlineThickness(float thickness);
				const sf::Texture* getTexture() const;
				const intRect& getTextureRect() const;
				const color& getFillColor() const;
				const color& getOutlineColor() const;
				float getOutlineThickness() const;
				virtual floatRect getLocalBounds() const override;
				virtual floatRect getGlobalBounds() const override;

				virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			protected:
				virtual void ensureGeometryUpdate() const override;
				void setTexture_(const sf::Texture* texture, bool resetRect = false);
				void updateFillColors();
				void updateTexCoords();
				void updateOutline();
				void updateOutlineColors();

			private:
				const sf::Texture* m_texture;
				sf::Vector2f _size;
				u32 m_pointCount;
				intRect m_textureRect;
				color m_fillColor;
				color m_outlineColor;
				float m_outlineThickness;
				mutable sf::VertexArray m_outlineVertices;
				mutable floatRect m_insideBounds;
			};
		}
	}
}

#endif
