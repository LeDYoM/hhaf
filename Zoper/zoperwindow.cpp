#include "zoperwindow.hpp"

using namespace sf;

namespace zoper
{
	ZoperWindow::ZoperWindow()
	{
		create(1024, 768, 32, "Zoper");
	}

	ZoperWindow::~ZoperWindow()
	{
	}

	void ZoperWindow::onCreate()
	{
		Window::onCreate();
	}

	void ZoperWindow::onDestroy()
	{
		Window::onDestroy();
	}

}
