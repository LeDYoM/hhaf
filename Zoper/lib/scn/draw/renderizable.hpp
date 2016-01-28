#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "../../log.hpp"
#include "../../core/hasname.hpp"
#include "nodeshape.hpp"
#include "nodetext.hpp"
#include "idrawable.hpp"
#include <SFML/Graphics.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			enum class Alignment : u8
			{
				Left = 0,
				Center = 1,
				Right = 2
			};

			class Renderizable : public lib::core::HasName, public IDrawable, public sf::Transformable
			{
			public:
				explicit Renderizable(const std::string &name, lib::scn::draw::NodeText *text);
				explicit Renderizable(const std::string &name, lib::scn::draw::NodeShape *circleShape);

				virtual ~Renderizable();

				inline lib::scn::draw::NodeText *const getAsText() const { __ASSERT(_activeDrawNode == ActiveDrawNode::Text, "Node is not a text"); return _drawNodeData.text; }
				inline lib::scn::draw::NodeShape *const getAsEllipseShape() const { __ASSERT(_activeDrawNode == ActiveDrawNode::EllipseShape, "Node is not an ellipse shape"); return _drawNodeData.ellipseShape; }

				virtual u32 draw(lib::core::Window *window, sf::RenderStates &states) override;
				void setColor(const sf::Color &color);

				sf::FloatRect getLocalBounds();
				sf::FloatRect getGlobalBounds();

				// Some useful shortcuts
				using sf::Transformable::setPosition;
				void setPosition(const sf::Vector2f &pos, Alignment alignment);
				void setPositionX(const float x, Alignment alignment = Alignment::Left);
				void setPositionY(const float y, Alignment alignment = Alignment::Left);
				void setAlignment(Alignment alignment);
			private:
				union DrawNodeData
				{
					NodeText *text{ nullptr };
					NodeShape *ellipseShape;
				} _drawNodeData;
				enum class ActiveDrawNode : u8
				{
					Empty = 0,
					Text = 1,
					EllipseShape = 2,
				} _activeDrawNode{ ActiveDrawNode::Empty };
			};
		}
	}
}

#endif
