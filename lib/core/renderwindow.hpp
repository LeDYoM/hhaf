#ifndef __LIB_EXTERNAL_REDNERWINDOW_HPP__
#define __LIB_EXTERNAL_REDNERWINDOW_HPP__

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

namespace lib
{
	namespace core
	{
		namespace external
		{
			class RenderWindow : public sf::Window, public sf::RenderTarget
			{
			public:

				RenderWindow();
				RenderWindow(sf::VideoMode mode, const std::string& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
				explicit RenderWindow(sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
				virtual ~RenderWindow();

				virtual sf::Vector2u getSize() const override;

				virtual bool activate(bool active = true) override { return setActive(active); }

			protected:

				virtual void onCreate();
				virtual void onResize();
			};
		}
	}
}
#endif

