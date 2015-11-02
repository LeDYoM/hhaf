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

			Renderizable::~Renderizable()
			{
				LOG_DESTRUCT("Name: " << name());
				delete _drawNodeData.text;
			}
		}
	}
}
