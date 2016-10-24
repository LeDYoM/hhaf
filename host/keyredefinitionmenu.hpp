#ifndef __KEYREDEFINITONMENU_HPP__
#define __KEYREDEFINITONMENU_HPP__

#include <lib/menu/menustep.hpp>
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
			const std::string getKeyNameStr(const lib::u32 index) const;
			void setTextForKey();

			lib::u32 _indexKey;
			KeyMapping _keyMapping;
			lib::sptr<lib::scn::draw::NodeText> _nextKeyText{ nullptr };
		};
	}
}

#endif
