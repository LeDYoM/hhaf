#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include <lib/include/types.hpp>
#include <SFML/Graphics.hpp>
#include "renderizable.hpp"

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
				explicit NodeShape(const std::string &name, const vector2df& size, const u32 pointCount=4,const NodeMode mode=NodeMode::Shape);
				virtual ~NodeShape();
				void setSize(const sf::Vector2f &size);
				void setSize(const float size);
				const sf::Vector2f &getSize() const;
				u32 getPointCount() const;
				void setPointCount(lib::u32 numPoints);
				virtual sf::Vector2f getPoint(lib::u32 index) const;
				void setTexture(const sf::Texture *texture, bool resetSize=true, bool resetRect = false);

				void setTextureRect(const sf::IntRect& rect);
				virtual void setColor(const sf::Color& color) override;
				const sf::Texture* getTexture() const;
				const sf::IntRect& getTextureRect() const;
				const sf::Color& getFillColor() const;
				const sf::Color& getOutlineColor() const;
				float getOutlineThickness() const;
				sf::FloatRect getLocalBounds() const override;
				sf::FloatRect getGlobalBounds() const override;

			protected:
				void update();
				void setTexture_(const sf::Texture* texture, bool resetRect = false);
				virtual u32 draw(lib::core::Window *window, sf::RenderStates &states) override;
				void updateFillColors();
				void updateTexCoords();

			private:
				const sf::Texture* m_texture;
				sf::Vector2f _size;
				lib::u32 m_pointCount;
				sf::IntRect m_textureRect;
				sf::Color m_fillColor;
				sf::VertexArray m_vertices;
				sf::FloatRect m_bounds;
			};
		}
	}
}

#endif
