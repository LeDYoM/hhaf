#include <lib/include/main.hpp>
#include "zoperprogramcontroller.hpp"
#include <memory>

int main(int argc, char* argv[])
{
	return lib::libMain(argc, argv, std::make_unique<zoper::ZoperProgramController>());
}
