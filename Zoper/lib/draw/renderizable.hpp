#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include <SFML/Graphics.hpp>
#include "../log.hpp"
#include "../core/hasname.hpp"

namespace lib
{
	namespace draw
	{
		class Renderizable : public lib::core::HasName
		{
		public:
			union DrawNodeData
			{
				sf::Drawable *drawable{ nullptr };
				sf::Transformable *transformable;
				sf::Text *text;
				sf::Sprite *sprite;
				sf::Shape *shape;
			};
			enum ActiveDrawNode
			{
				Empty=0,
				Text=1,
				Sprite=2,
				Shape=3,
				MaxActiveDrawNode=0xffff
			};
			explicit Renderizable(const std::string &name, sf::Text *text);
			explicit Renderizable(const std::string &name, sf::Sprite *sprite);
			explicit Renderizable(const std::string &name, sf::Shape *shape);
			virtual ~Renderizable();

			inline sf::Drawable *const getAsDrawable() const { return _drawNodeData.drawable; }
			inline sf::Transformable *const getAsTransformable() const { return _drawNodeData.transformable; }
			inline sf::Text *const getAsText() const { __ASSERT(_activeDrawNode == ActiveDrawNode::Text, "Node is not a text"); return _drawNodeData.text; }
			inline sf::Sprite *const getAsSprite() const { /*__ASSERT(_activeDrawNode == ActiveDrawNode::Sprite, "Node is not a sprite");*/ return _drawNodeData.sprite; }
			inline sf::Shape *const getAsShape() const { /*__ASSERT(_activeDrawNode == ActiveDrawNode::Shape, "Node is not a shape");*/ return _drawNodeData.shape; }

		private:
			DrawNodeData _drawNodeData;
			ActiveDrawNode _activeDrawNode{ Empty };
		};
	}
}

#endif
