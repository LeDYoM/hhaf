#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <SFML/Graphics.hpp>
#include "renderizable.hpp"

namespace lib
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
			void setSize(const vector2df &size);
			void setSize(const float size);
			const vector2df &getSize() const;
			u32 getPointCount() const;
			void setPointCount(lib::u32 numPoints);
			virtual vector2df getPoint(u32 index) const;
			void setTexture(const sf::Texture *texture, bool resetSize=true, bool resetRect = false);

			void setTextureRect(const sf::IntRect& rect);
			virtual void setColor(const sf::Color& color) override;
			const sf::Texture* getTexture() const;
			const sf::IntRect& getTextureRect() const;
			const sf::Color& getFillColor() const;
			Rectf32 getLocalBounds() const override;
			Rectf32 getGlobalBounds() const override;

		protected:
			void update();
			void setTexture_(const sf::Texture* texture, bool resetRect = false);
			virtual u32 draw(sf::RenderStates &states) override;
			void updateFillColors();
			void updateTexCoords();

		private:
			const sf::Texture* m_texture;
			vector2df _size;
			u32 m_pointCount;
			sf::IntRect m_textureRect;
			sf::Color m_fillColor;
			sf::VertexArray m_vertices;
			Rectf32 m_bounds;
		};
	}
}

#endif
