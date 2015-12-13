#include "lib/compileconfig.hpp"
#include "lib/memmanager.hpp"
#include "lib/log.hpp"

#include "zoperprogramcontroller.hpp"
#include <SFML/Window.hpp>

int main(int argc, char* argv[])
{
	initLog();
	installMemManager();
	zoper::ZoperProgramController *program = new zoper::ZoperProgramController;

	program->start();
	int result = program->loop();

	delete program;
	finishMemManager();
	finishLog();
	return result;
}
