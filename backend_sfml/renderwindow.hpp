#ifndef LIB_BACKEND_REDNERWINDOW_HPP__
#define LIB_BACKEND_REDNERWINDOW_HPP__

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/vertexarray.hpp>
#include <lib/include/iapp.hpp>
#include <lib/backend/iwindow.hpp>

#include <queue>

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

				bool createWindow(const WindowCreationParams &wcp) override;
				sf::Vector2u getSize() const override;
				bool activate(bool active = true) override { return setActive(active); }
				void draw(const scene::Vertex *vertices, const u32 nVertex, const scene::PrimitiveType pType, const f32 *transform, const ITexture *texture) override;

				void setViewport(const Rectf32 &nviewport) override;
				Rectf32 viewPort() const override;
				void setViewRect(const Rectf32 &nviewRect) override;
				Rectf32 viewRect() const override;

				bool processEvents() override;
				void display() override;
				void clear() override;
				void setWindowTitle(const inline_str &newTitle) override;
				void closeWindow() override;

				// Input part
				bool arePendingKeyPresses() const override;
				bool arePendingKeyReleases() const override;

				input::Key popKeyPress() override;
				input::Key popKeyRelease() override;

			protected:
				virtual void onCreate();
				virtual void onResize();

			private:
				void keyEvent(const sf::Event &e);

				std::queue<input::Key> m_keysPressed;
				std::queue<input::Key> m_keysReleased;
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

