#include "renderizable.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			Renderizable::Renderizable(const std::string &name, sf::Text *text)
				: HasName{ name }
			{
				LOG_CONSTRUCT("Name: " << name << " of type text");

				_drawNodeData.text = text;
				_drawNodeAsDrawable = text;
				_drawNodeAsTransformable = text;
				_activeDrawNode = ActiveDrawNode::Text;
			}

			Renderizable::Renderizable(const std::string &name, sf::Sprite *sprite)
				: HasName{ name }
			{
				LOG_CONSTRUCT("Name: " << name << " of type sprite");

				_drawNodeData.sprite = sprite;
				_drawNodeAsDrawable = sprite;
				_drawNodeAsTransformable = sprite;
				_activeDrawNode = ActiveDrawNode::Sprite;
			}


			Renderizable::Renderizable(const std::string & name, sf::CircleShape * circleShape)
				: HasName{ name }
			{
				LOG_CONSTRUCT("Name: " << name << " of type circleShape");
				_drawNodeData.circleShape = circleShape;
				_drawNodeAsDrawable = circleShape;
				_drawNodeAsTransformable = circleShape;
				_activeDrawNode = ActiveDrawNode::CircleShape;

			}

			Renderizable::Renderizable(const std::string & name, lib::scn::draw::EllipseShape * ellipseShape)
				: HasName{ name }
			{
				LOG_CONSTRUCT("Name: " << name << " of type ellipseShape");
				_drawNodeData.ellipseShape = ellipseShape;
				_drawNodeAsDrawable = ellipseShape;
				_drawNodeAsTransformable = ellipseShape;
				_activeDrawNode = ActiveDrawNode::EllipseShape;

			}

			Renderizable::~Renderizable()
			{
				switch (_activeDrawNode)
				{
				default:
				case ActiveDrawNode::Empty:
					__ASSERT(!_drawNodeData.text, "Empty draw node data containing data at deletion time");
					LOG_DESTRUCT("Name: " << name() << " and type <not defined>");
					delete _drawNodeData.text;
					break;
				case ActiveDrawNode::Text:
					LOG_DESTRUCT("Name: " << name() << " and type Text");
					delete _drawNodeData.text;
					break;
				case ActiveDrawNode::Sprite:
					LOG_DESTRUCT("Name: " << name() << " and type Sprite");
					delete _drawNodeData.sprite;
					break;
				case ActiveDrawNode::CircleShape:
					LOG_DESTRUCT("Name: " << name() << " and type CircleShape");
					delete _drawNodeData.circleShape;
					break;
				case ActiveDrawNode::EllipseShape:
					LOG_DESTRUCT("Name: " << name() << " and type EllipseShape");
					delete _drawNodeData.ellipseShape;
					break;
				}
			}
		}
	}
}
