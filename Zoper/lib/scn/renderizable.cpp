#include "renderizable.hpp"

namespace lib
{
	namespace scn
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
			_activeDrawNode = ActiveDrawNode::Sprite;
		}

		Renderizable::Renderizable(const std::string &name, sf::Shape *shape)
			: HasName{ name }
		{
			LOG_CONSTRUCT("Name: " << name << " of type shape");

			_drawNodeData.shape = shape;
			_activeDrawNode = ActiveDrawNode::Shape;
		}

		Renderizable::Renderizable(const std::string & name, sf::CircleShape * circleShape)
			: HasName{ name }
		{
			LOG_CONSTRUCT("Name: " << name << " of type circleShape");
			_drawNodeData.shape = circleShape;
			_activeDrawNode = ActiveDrawNode::CircleShape;

		}

		Renderizable::~Renderizable()
		{
			LOG_DESTRUCT("Name: " << name());
			delete _drawNodeData.text;
		}
	}
}
