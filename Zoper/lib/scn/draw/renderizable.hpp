#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "../../log.hpp"
#include "../../core/hasname.hpp"
#include "ellipseshape.hpp"
#include <SFML/Graphics.hpp>


namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class Renderizable : public lib::core::HasName
			{
			public:
				explicit Renderizable(const std::string &name, sf::Text *text);
				explicit Renderizable(const std::string &name, sf::Sprite *sprite);
				explicit Renderizable(const std::string &name, sf::CircleShape *circleShape);
				explicit Renderizable(const std::string &name, lib::scn::draw::EllipseShape *circleShape);

				virtual ~Renderizable();

				inline sf::Drawable *const getAsDrawable() const { return _drawNodeAsDrawable; }
				inline sf::Transformable *const getAsTransformable() const { return _drawNodeAsTransformable; }
				inline sf::Text *const getAsText() const { __ASSERT(_activeDrawNode == ActiveDrawNode::Text, "Node is not a text"); return _drawNodeData.text; }
				inline sf::Sprite *const getAsSprite() const { __ASSERT(_activeDrawNode == ActiveDrawNode::Sprite, "Node is not a sprite"); return _drawNodeData.sprite; }
				inline sf::CircleShape *const getAsCircleShape() const { __ASSERT(_activeDrawNode == ActiveDrawNode::CircleShape, "Node is not a circle shape"); return _drawNodeData.circleShape; }
				inline lib::scn::draw::EllipseShape *const getAsEllipseShape() const { __ASSERT(_activeDrawNode == ActiveDrawNode::EllipseShape, "Node is not an ellipse shape"); return _drawNodeData.ellipseShape; }

				// Some useful shortcuts
				inline void setPosition(const sf::Vector2f &pos) { getAsTransformable()->setPosition(pos); }
				inline bool isVisible() const { return visible; }
				inline void setVisible(bool nv) { visible = nv; }

			private:
				union DrawNodeData
				{
					sf::Text *text{ nullptr };
					sf::Sprite *sprite;
					sf::CircleShape *circleShape;
					EllipseShape *ellipseShape;
				} _drawNodeData;
				sf::Drawable *_drawNodeAsDrawable{ nullptr };
				sf::Transformable *_drawNodeAsTransformable{ nullptr };
				bool visible{ true };
				enum class ActiveDrawNode
				{
					Empty = 0,
					Text = 1,
					Sprite = 2,
					CircleShape = 3,
					EllipseShape = 4,
					MaxActiveDrawNode = 0xffff
				} _activeDrawNode{ ActiveDrawNode::Empty };
			};
		}
	}
}

#endif
