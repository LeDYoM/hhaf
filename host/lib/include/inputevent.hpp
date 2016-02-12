#ifndef __LIB_EVENT_INPUTEVENT_HPP__
#define __LIB_EVENT_INPUTEVENT_HPP__

#include <lib/include/key.hpp>
#include "event.hpp"

namespace lib
{
	namespace events
	{
		class InputEvent : public Event
		{
		public:
			enum class Action
			{
				KeyPressed,
				KeyReleased
			};
			InputEvent(const Action &_action) : action{ _action } {}
			const Action action;
			InputEvent &operator=(const InputEvent &rho) = delete;
		};

		class KeyPressedEvent : public InputEvent
		{
		public:
			KeyPressedEvent(const input::Key key_) : InputEvent{ Action::KeyPressed }, key{ key_ } {}
			const input::Key key;
		};

		class KeyReleasedEvent : public InputEvent
		{
		public:
			KeyReleasedEvent(const input::Key key_) : InputEvent{ Action::KeyPressed }, key{ key_ } {}
			const input::Key key;
		};
	}
}

#endif
