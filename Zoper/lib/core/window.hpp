#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "../types.hpp"

namespace lib
{
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
		private:
			uptr<WindowPrivate> p_wPrivate{ nullptr };
		};
	}
}

#endif
