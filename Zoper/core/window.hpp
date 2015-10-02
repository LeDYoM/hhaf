#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <string>

namespace lib
{
	namespace core
	{
		class Window : public sf::Window
		{
		public:
			Window();
			virtual ~Window();
			void create(int w, int h, int bpp, const std::string &title);
			void loop();

		protected:
			virtual void onCreate();
			virtual void onDestroy();
		};
	}
}

#endif
