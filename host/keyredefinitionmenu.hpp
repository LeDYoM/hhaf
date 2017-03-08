#ifndef __KEYREDEFINITONMENU_HPP__
#define __KEYREDEFINITONMENU_HPP__

#include "keymapping.hpp"
#include <lib/gui/choosecontrol.hpp>

namespace zoper
{
	namespace zmenu
	{
		class KeyRedefinitionMenu : public lib::draw::SceneNode
		{
		public:
			constexpr static char* ClassName = "KeyRedefinitionMenu";

			KeyRedefinitionMenu(lib::draw::SceneNode *parent);
			virtual ~KeyRedefinitionMenu();
			virtual void create() override;

		private:
			const std::string getKeyNameStr(const lib::u32 index) const;
			void setTextForKey();

			lib::u32 _indexKey;
			KeyMapping _keyMapping;
			lib::sptr<lib::draw::nodes::NodeText> _nextKeyText{ nullptr };
		};
	}
}

#endif