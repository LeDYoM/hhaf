#include <locale>
#include "window.hpp"
#include "compileconfig.hpp"
#include "log.hpp"
#include "randomizer.hpp"
#include "timer.hpp"
#include "host.hpp"
#include <lib/include/iapp.hpp>
#include <lib/core/events/event.hpp>
#include <lib/core/events/inputevent.hpp>
#include <lib/core/events/eventmanager.hpp>

namespace lib
{
	namespace core
	{
		namespace
		{
			sf::String getAsString(const std::string &other)
			{
				std::wstring wsTmp(other.begin(), other.end());
				sf::String temp(wsTmp);
				return temp;
			}

			lib::input::Key doCast(const sf::Keyboard::Key &k)
			{
				int temp = k;
				return static_cast<lib::input::Key>(temp);
			}
		}
		struct WindowPrivate
		{
			Timer globalClock;
			u64 lastTimeFps{ 0 };
			s32 lastFps{ 0 };
			s32 currentFps{ 0 };
			Randomizer randomizer;
		};

		Window::Window(const WindowCreationParams &wcp)
			: p_wPrivate{ new WindowPrivate() }, _title(wcp.windowTitle)
		{
			logConstruct_NOPARAMS;
			create(wcp);
		}

		Window::~Window()
		{
			logDestruct_NOPARAMS;
		}

		void Window::create(const WindowCreationParams &wcp)
		{
			logDebug("Going to create Window");
			logDebug("Resolution:", wcp.width, "x", wcp.height ,"x", wcp.bpp);
			logDebug("Fullscreen:" , wcp.fullScreen);
			logDebug("Antialiasing:", wcp.antialiasing);

			sf::Uint32 style{ sf::Style::Titlebar | sf::Style::Close };
			if (wcp.fullScreen)
				style = sf::Style::Fullscreen;

			// Deal with SFML bug
			sf::Window::create(sf::VideoMode(wcp.width, wcp.height, wcp.bpp), getAsString(_title), style,sf::ContextSettings(0,0,wcp.antialiasing));

			this->setVerticalSyncEnabled(wcp.vsync);
		}

		bool Window::preLoop()
		{
			auto eMs = p_wPrivate->globalClock.getElapsedTime().asMilliSeconds();
			if ((eMs - p_wPrivate->lastTimeFps) > 1000) {
				p_wPrivate->lastTimeFps = eMs;
				p_wPrivate->lastFps = p_wPrivate->currentFps;
				p_wPrivate->currentFps = 0;
				setTitle(getAsString(_title + " FPS:" + std::to_string(p_wPrivate->lastFps)));
			}
			++(p_wPrivate->currentFps);
			clear();

			sf::Event event;
			while (pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					return true;
				} else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
					keyEvent(event);
				}
			}
			return false;
		}

		void Window::postLoop()
		{
			display();
		}

		void Window::onCreate()
		{
			logDebug("Window created");
		}

		void Window::onDestroy()
		{
			logDebug("Going to close Window");
			close();
			logDebug("Window closed");
		}

		u32 Window::getRandomNumer(u32 max /*= 1*/, u32 min /*= 0*/)
		{
			return p_wPrivate->randomizer.getUInt(max, min);
		}

		void Window::keyEvent(sf::Event e)
		{
			_ASSERT(e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased);

			using namespace lib::events;

			if (e.type == sf::Event::KeyPressed) {
				host().eventManager().addEvent(uptr<KeyPressedEvent>(new KeyPressedEvent{doCast(e.key.code)}));
			}
			else {
				host().eventManager().addEvent(uptr<KeyReleasedEvent>(new KeyReleasedEvent{ doCast(e.key.code) }));
			}
		}
	}
}
