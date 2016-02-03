#include <lib/core/compileconfig.hpp>
#include <lib/core/memmanager.hpp>
#include <lib/core/log.hpp>

#include "zoperprogramcontroller.hpp"
#include <SFML/Window.hpp>

int main(int argc, char* argv[])
{
	argc;
	argv;
	int result = -1;

	try
	{
		initLog();
		installMemManager();
		zoper::ZoperProgramController *program = new zoper::ZoperProgramController;

		program->start();
		result = program->loop();

		delete program;
		finishMemManager();
		finishLog();
	}
	catch (...)
	{
		
	}
	return result;
}
