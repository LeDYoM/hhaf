#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "../types.hpp"

namespace lib
{
	class Randomizer;
	namespace scn
	{
		class SceneManager;
	}
	namespace core
	{
		struct WindowPrivate;
		class ProgramController;

		class Window : public sf::RenderWindow
		{
		public:
			Window(ProgramController *parentController);
			virtual ~Window();
			void create(int w, int h, int bpp, const std::string &title);
			bool loopStep();
			virtual void onCreate();
			virtual void onDestroy();
			u32 getRandomNumer(u32 max = 1, u32 min = 0);

		private:
			sptr<lib::scn::SceneManager> p_sceneManager;
			uptr<WindowPrivate> p_wPrivate{ nullptr };
			ProgramController *p_parentController;

			void keyEvent(sf::Event e);
		};
	}
}

#endif
