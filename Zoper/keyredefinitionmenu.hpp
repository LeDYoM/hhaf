#ifndef __KEYREDEFINITONMENU_HPP__
#define __KEYREDEFINITONMENU_HPP__

#include "lib/menu/menustep.hpp"
#include "lib/configuration.hpp"
#include "keymapping.hpp"

namespace zoper
{
	namespace zmenu
	{
		class KeyRedefinitionMenu : public lib::menu::MenuStep
		{
		public:
			KeyRedefinitionMenu();
			virtual ~KeyRedefinitionMenu();
			virtual void onCreate() override;

		private:
			KeyMapping _keyMapping;
//			sf::Keyboard::Key 
			lib::Configuration _gameConfig;
			lib::sptr<lib::scn::draw::Renderizable> _nextKeyText{ nullptr };
		};
	}
}

#endif
