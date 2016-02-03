#include "renderizable.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			Renderizable::Renderizable(const std::string &name)
				: HasName{ name }
			{
				LOG_CONSTRUCT("Name: " << name << " of type");

			}

			u32 Renderizable::draw(lib::core::Window *window, sf::RenderStates &states)
			{
				window;
				states;
				if (isVisible())
				{
//					window->draw()
//					window->draw(*getAsDrawable(),states);
					return 1;
				}
				return 0;
			}

			Renderizable::~Renderizable()
			{
			}

			void Renderizable::setPosition(const sf::Vector2f &pos, Alignment alignment)
			{
				switch (alignment)
				{
				default:
				case lib::scn::draw::Alignment::Left:
					sf::Transformable::setPosition(pos);
					break;
				case lib::scn::draw::Alignment::Center:
					sf::Transformable::setPosition(sf::Vector2f{ pos.x - (getLocalBounds().width / 2.0f), pos.y - (getLocalBounds().height / 2.0f) });
					break;
				case lib::scn::draw::Alignment::Right:
					sf::Transformable::setPosition(sf::Vector2f{ pos.x - (getLocalBounds().width), pos.y - (getLocalBounds().height) });
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
				setPosition(getPosition(), alignment);
			}
		}
	}
}
