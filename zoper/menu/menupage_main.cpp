#include "menupage.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{

			MenuPageMain::MenuPageMain(lib::scene::SceneNode *parent, str name) : SceneNode{ parent, std::move(name) } {}

			MenuPage::~MenuPage() = default;

			void MenuPage::create()
			{
			}
		}
	}
}
