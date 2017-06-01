#ifndef LIB_BACKEND_REDNERWINDOW_HPP__
#define LIB_BACKEND_REDNERWINDOW_HPP__

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/scene/vertexarray.hpp>
#include <lib/scene/renderstatesstack.hpp>
#include <lib/include/iapp.hpp>
#include <lib/backend/iwindow.hpp>

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			class RenderWindow : public IWindow, public sf::Window, public sf::RenderTarget
			{
			public:

				virtual ~RenderWindow();

				virtual bool createWindow(const WindowCreationParams &wcp) override;
				virtual sf::Vector2u getSize() const override;
				virtual bool activate(bool active = true) override { return setActive(active); }
				virtual void draw(const scene::VertexArray &vertices, const scene::RenderStatesStack& states) override;

				virtual void setViewport(const Rectf32 &nviewport) override;
				virtual Rectf32 viewPort() const override;
				virtual void setViewRect(const Rectf32 &nviewRect) override;
				virtual Rectf32 viewRect() const override;

				virtual bool processEvents() override;
				virtual void display() override;
				virtual void clear() override;
				virtual void setWindowTitle(const str newTitle) override;
				virtual void closeWindow() override;

			protected:
				virtual void onCreate();
				virtual void onResize();

			private:
				void keyEvent(const sf::Event &e);
			};
			class WindowBackendInfo : public IWindowProviderInfo
			{
			public:
				virtual const char *const info() override;
			};
		}
	}
}
#endif
