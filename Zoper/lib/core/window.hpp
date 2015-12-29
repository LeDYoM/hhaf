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
		struct WindowCreationParams;
		class ProgramController;

		class Window : public sf::RenderWindow
		{
		public:
			Window(ProgramController *parentController, const WindowCreationParams &wcp);
			virtual ~Window();
			bool loopStep();
			virtual void onCreate();
			virtual void onDestroy();
			u32 getRandomNumer(u32 max = 1, u32 min = 0);
			void exitProgram();

		private:
			void create(const WindowCreationParams &wcp);

			sptr<lib::scn::SceneManager> p_sceneManager;
			uptr<WindowPrivate> p_wPrivate{ nullptr };
			ProgramController *p_parentController;
			bool _shouldClose{ false };
			void keyEvent(sf::Event e);
			std::string _title;
		};
	}
}

#endif
