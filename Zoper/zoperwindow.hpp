#ifndef __ZOOPERWINDOW_HPP_
#define __ZOOPERWINDOW_HPP_

#include "core/window.hpp"

namespace zoper
{
	class ZoperWindow : public lib::core::Window
	{
	public:
		ZoperWindow();
		virtual ~ZoperWindow();
	protected:
		void onCreate();
		void onDestroy();
	};
}

#endif
