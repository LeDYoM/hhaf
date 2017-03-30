#ifndef LIB_BACKEND_REDNERWINDOW_HPP__
#define LIB_BACKEND_REDNERWINDOW_HPP__

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/draw/vertexarray.hpp>
#include <lib/draw/renderstates.hpp>
#include <lib/include/iapp.hpp>

namespace lib
{
	namespace backend
	{
		class RenderWindow : public sf::Window, public sf::RenderTarget
		{
		public:

			virtual ~RenderWindow();

			bool createWindow(const WindowCreationParams &wcp);
			virtual sf::Vector2u getSize() const override;
			virtual bool activate(bool active = true) override { return setActive(active); }
			void draw(const draw::VertexArray &vertices, const draw::RenderStates& states);

			void setViewport(const Rectf32 &nviewport);
			Rectf32 viewPort() const;
			void setViewRect(const Rectf32 &nviewRect);
			Rectf32 viewRect() const;

			virtual bool processEvents();

		protected:
			virtual void onCreate();
			virtual void onResize();

		private:
			void keyEvent(sf::Event e);

		};
	}
}
#endif

