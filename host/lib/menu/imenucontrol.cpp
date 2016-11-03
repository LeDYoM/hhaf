#include "imenucontrol.hpp"
#include "choosecontrol.hpp"

namespace lib
{
	namespace menu
	{
		void IMenuControl::addChooseControl(sptr<ChooseControl> cc)
		{
			addRenderGroup(cc);
		}
	}
}
