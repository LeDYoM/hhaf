#include "renderizable.hpp"
#include "../../core/window.hpp"

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

			u32 Renderizable::draw(lib::core::Window *window, sf::RenderStates &states) const
			{
				if (isVisible())
				{
					window->draw(*getAsDrawable(),states);
					return 1;
				}
				return 0;
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

			sf::FloatRect Renderizable::getLocalBounds()
			{
				// For some reason SFML does not have inheritance in these methods, so let's wrap it
				__ASSERT(!_drawNodeData.text, "Empty draw node data");
				switch (_activeDrawNode)
				{
				default:
				case ActiveDrawNode::Empty:
					return sf::FloatRect();
					break;
				case ActiveDrawNode::Text:
					return getAsText()->getLocalBounds();
					break;
				case ActiveDrawNode::Sprite:
					return getAsSprite()->getLocalBounds();
					break;
				case ActiveDrawNode::CircleShape:
					return getAsCircleShape()->getLocalBounds();
					break;
				case ActiveDrawNode::EllipseShape:
					return getAsEllipseShape()->getLocalBounds();
					break;
				}
			}

			sf::FloatRect Renderizable::getGlobalBounds()
			{
				// For some reason SFML does not have inheritance in these methods, so let's wrap it
				__ASSERT(!_drawNodeData.text, "Empty draw node data");
				switch (_activeDrawNode)
				{
				default:
				case ActiveDrawNode::Empty:
					return sf::FloatRect();
					break;
				case ActiveDrawNode::Text:
					return getAsText()->getGlobalBounds();
					break;
				case ActiveDrawNode::Sprite:
					return getAsSprite()->getGlobalBounds();
					break;
				case ActiveDrawNode::CircleShape:
					return getAsCircleShape()->getGlobalBounds();
					break;
				case ActiveDrawNode::EllipseShape:
					return getAsEllipseShape()->getGlobalBounds();
					break;
				}
			}

			void Renderizable::setPosition(const sf::Vector2f &pos, Alignment alignment /*= Alignment::Left*/)
			{
				switch (alignment)
				{
				default:
				case lib::scn::draw::Alignment::Left:
					getAsTransformable()->setPosition(pos);
					break;
				case lib::scn::draw::Alignment::Center:
					setPosition(sf::Vector2f{ pos.x - (getLocalBounds().width / 2.0f), pos.y - (getLocalBounds().height / 2.0f) });
					break;
				case lib::scn::draw::Alignment::Right:
					setPosition(sf::Vector2f{ pos.x - (getLocalBounds().width), pos.y - (getLocalBounds().height) });
					break;
				}
			}

			void Renderizable::setPositionX(const float x, Alignment alignment /*= Alignment::Left*/)
			{
				const sf::Vector2f position( getAsTransformable()->getPosition() );
				switch (alignment)
				{
				default:
				case lib::scn::draw::Alignment::Left:
					getAsTransformable()->setPosition(sf::Vector2f{ x, position.y });
					break;
				case lib::scn::draw::Alignment::Center:
					getAsTransformable()->setPosition(sf::Vector2f{ x - (getLocalBounds().width / 2.0f), position.y });
					break;
				case lib::scn::draw::Alignment::Right:
					getAsTransformable()->setPosition(sf::Vector2f{ x - (getLocalBounds().width), position.y });
					break;
				}
			}

			void Renderizable::setPositionY(const float y, Alignment alignment /*= Alignment::Left*/)
			{
				const sf::Vector2f position(getAsTransformable()->getPosition());
				switch (alignment)
				{
				default:
				case lib::scn::draw::Alignment::Left:
					getAsTransformable()->setPosition(sf::Vector2f{ position.x, y });
					break;
				case lib::scn::draw::Alignment::Center:
					getAsTransformable()->setPosition(sf::Vector2f{ position.x, y - (getLocalBounds().height / 2.0f) });
					break;
				case lib::scn::draw::Alignment::Right:
					getAsTransformable()->setPosition(sf::Vector2f{ position.x, y - (getLocalBounds().height) });
					break;
				}
			}

			void Renderizable::setAlignment(Alignment alignment)
			{
				setPosition(getAsTransformable()->getPosition(), alignment);
			}

		}
	}
}
