#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

namespace lib
{
	namespace core
	{
		struct WindowPrivate;

		class Window : public sf::Window
		{
		public:
			Window();
			virtual ~Window();
			void create(int w, int h, int bpp, const std::string &title);
			bool loopStep();
			virtual void onCreate();
			virtual void onDestroy();
		private:
			std::unique_ptr<WindowPrivate> p_wPrivate{ nullptr };
		};
	}
}

#endif
