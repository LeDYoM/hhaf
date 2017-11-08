#include "menupageinputcomponent.hpp"
#include <mtypes/include/log.hpp>


namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	void MenuPageInputComponent::onAttached()
	{
		InputComponent::KeyPressed.connect([this](const input::Key&key) {
			switch (key) {
			case input::Key::Left:
				Left();
				break;
			case input::Key::Right:
				Right();
				break;
			case input::Key::Up:
				Up();
				break;
			case input::Key::Down:
				Down();
				break;
			case input::Key::Return:
				Selected();
				break;
			default:
				break;
			}
		});
//		InputComponent::KeyReleased.connect(keyReleased);
	}

}
