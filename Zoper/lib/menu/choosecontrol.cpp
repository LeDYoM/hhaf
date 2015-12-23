#include "choosecontrol.hpp"

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, const std::vector<std::string> labels)
			: scn::draw::RenderGroup{ name }
		{
			for (const auto label : labels)
			{

			}
		}


		ChooseControl::~ChooseControl()
		{
		}
	}
}
