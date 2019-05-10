#include <lib/include/key.hpp>

#include "inputdriver.hpp"
#include "conversions.hpp"

namespace lib::backend::sfmlb
{
	void InputDriver::keyEvent(const sf::Event &e)
	{
		const auto k(doCast(e.key.code));
		if (k != input::Key::Unknown)
		{
			if (e.type == sf::Event::KeyPressed)
			{
				keyPressed(k);
			}
			else if (e.type == sf::Event::KeyReleased) 
			{
				keyReleased(k);
			}
		}
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
	input::Key popKey(T &container) 
	{
		input::Key k(input::Key::Unknown);
		if (!container.empty()) 
		{
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

	void InputDriver::keyPressed(const input::Key k)
	{
		m_keysPressed.push(k);
	}

	void InputDriver::keyReleased(const input::Key k)
	{
		m_keysReleased.push(k);
	}
}
