#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "../types.hpp"

namespace lib
{
	class Randomizer;
	namespace core
	{
		struct WindowPrivate;

		class Window : public sf::RenderWindow
		{
		public:
			Window();
			virtual ~Window();
			void create(int w, int h, int bpp, const std::string &title);
			bool loopStep();
			virtual void onCreate();
			virtual void onDestroy();
			u32 getRandomNumer(u32 max = 1, u32 min = 0);
		private:
			uptr<WindowPrivate> p_wPrivate{ nullptr };
			void keyEvent(sf::Event e);
		};
	}
}

#endif
