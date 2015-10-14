#include "lib/compileconfig.hpp"
#include "zoperprogramcontroller.hpp"
#include "lib/log.hpp"
#include <SFML/Window.hpp>

int main2(int argc, char* argv[])
{
	installMemManager();
	sf::Window *window = new sf::Window(sf::VideoMode(800, 600, 32), "SFML Window");

	// run the program as long as the window is open
	while (window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}

	delete window;
	finishMemManager();
	return 0;
}


int main(int argc, char* argv[])
{
	installMemManager();
	zoper::ZoperProgramController *program = new zoper::ZoperProgramController;

	program->start();
	int result = program->loop();

	delete program;
	finishMemManager();
	finishLog();
	return result;
}
