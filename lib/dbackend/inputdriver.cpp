#include "inputdriver.hpp"

#include <lib/include/key.hpp>
#include <lib/core/file.hpp>

namespace lib::backend::dback
{
    InputDriver::InputDriver()
    {
        FileInput finput()

    }

	bool InputDriver::arePendingKeyPresses() const
	{
		return !m_keysPressed.empty();
	}

	bool InputDriver::arePendingKeyReleases() const
	{
		return !m_keysReleased.empty();
	}

	template <typename T>
	input::Key popKey(T &container) {
		input::Key k(input::Key::Unknown);
		if (!container.empty()) {
			k = container.front();
			container.pop();
		}
		return k;
	}

	input::Key InputDriver::popKeyPress()
	{
		return popKey(m_keysPressed);
	}

	input::Key InputDriver::popKeyRelease()
	{
		return popKey(m_keysReleased);
	}
}
