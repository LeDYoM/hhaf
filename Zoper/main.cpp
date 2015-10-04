#include "zoperprogramcontroller.hpp"

int main(int argc, char* argv[])
{
	zoper::ZoperProgramController *program = new zoper::ZoperProgramController;

	program->start();
	int result = program->loop();

	delete program;
}
