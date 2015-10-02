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
			void setTitle(const std::string &title);
			virtual ~Window();
			void loop();

		protected:
			void onCreate();
			void onDestroy();
		};
	}
}

#endif
