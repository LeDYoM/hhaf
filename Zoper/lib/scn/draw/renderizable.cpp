#include "renderizable.hpp"
#include "../../core/window.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			Renderizable::Renderizable(const std::string &name, NodeText *text)
				: HasName{ name }
			{
				LOG_CONSTRUCT("Name: " << name << " of type text");

				_drawNodeData.text = text;
				_activeDrawNode = ActiveDrawNode::Text;
			}

			Renderizable::Renderizable(const std::string & name, NodeShape * ellipseShape)
				: HasName{ name }
			{
				LOG_CONSTRUCT("Name: " << name << " of type ellipseShape");

				_drawNodeData.ellipseShape = ellipseShape;
				_activeDrawNode = ActiveDrawNode::EllipseShape;
			}

			void Renderizable::draw(sf::RenderTarget &window, sf::RenderStates states) const
			{
				if (isVisible())
				{
					window.draw(*this,states);
				}
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
				case ActiveDrawNode::EllipseShape:
					LOG_DESTRUCT("Name: " << name() << " and type EllipseShape");
					delete _drawNodeData.ellipseShape;
					break;
				}
			}

			void Renderizable::setColor(const sf::Color &color)
			{
				switch (_activeDrawNode)
				{
				case ActiveDrawNode::Text:
					getAsText()->setColor(color);
					break;
				default:
				case ActiveDrawNode::EllipseShape:
					getAsEllipseShape()->setFillColor(color);
					break;
				}
			}

			floatRect Renderizable::getLocalBounds() const
			{
				// For some reason SFML does not have inheritance in these methods, so let's wrap it
				__ASSERT(_drawNodeData.text, "Empty draw node data");
				switch (_activeDrawNode)
				{
				default:
				case ActiveDrawNode::Empty:
					return sf::FloatRect();
					break;
				case ActiveDrawNode::Text:
					return getAsText()->getLocalBounds();
					break;
				case ActiveDrawNode::EllipseShape:
					return getAsEllipseShape()->getLocalBounds();
					break;
				}
			}

			floatRect Renderizable::getGlobalBounds() const
			{
				// For some reason SFML does not have inheritance in these methods, so let's wrap it
				__ASSERT(_drawNodeData.text, "Empty draw node data");
				switch (_activeDrawNode)
				{
				default:
				case ActiveDrawNode::Empty:
					return floatRect();
					break;
				case ActiveDrawNode::Text:
					return getAsText()->getGlobalBounds();
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
					sf::Transformable::setPosition(pos);
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
				const sf::Vector2f position( sf::Transformable::getPosition() );
				switch (alignment)
				{
				default:
				case lib::scn::draw::Alignment::Left:
					sf::Transformable::setPosition(sf::Vector2f{ x, position.y });
					break;
				case lib::scn::draw::Alignment::Center:
				{
					auto a = sf::Vector2f{ x - (getLocalBounds().width / 2.0f), position.y };
					sf::Transformable::setPosition(sf::Vector2f{ x - (getLocalBounds().width / 2.0f), position.y });
				}
					break;
				case lib::scn::draw::Alignment::Right:
					sf::Transformable::setPosition(sf::Vector2f{ x - (getLocalBounds().width), position.y });
					break;
				}
			}

			void Renderizable::setPositionY(const float y, Alignment alignment /*= Alignment::Left*/)
			{
				const sf::Vector2f position(sf::Transformable::getPosition());
				switch (alignment)
				{
				default:
				case lib::scn::draw::Alignment::Left:
					sf::Transformable::setPosition(sf::Vector2f{ position.x, y });
					break;
				case lib::scn::draw::Alignment::Center:
					sf::Transformable::setPosition(sf::Vector2f{ position.x, y - (getLocalBounds().height / 2.0f) });
					break;
				case lib::scn::draw::Alignment::Right:
					sf::Transformable::setPosition(sf::Vector2f{ position.x, y - (getLocalBounds().height) });
					break;
				}
			}

			void Renderizable::setAlignment(Alignment alignment)
			{
				setPosition(sf::Transformable::getPosition(), alignment);
			}

			void Renderizable::ensureGeometryUpdate() const
			{
//				throw std::logic_error("The method or operation is not implemented.");
			}

		}
	}
}
