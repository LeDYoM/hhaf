#ifndef __LIB_EVENT_INPUTEVENT_HPP__
#define __LIB_EVENT_INPUTEVENT_HPP__

#include <lib/include/key.hpp>
#include "event.hpp"
#include <lib/include/types.hpp>

namespace lib
{
	namespace events
	{
		class InputEvent
		{
		public:
			enum class Action
			{
				KeyPressed,
				KeyReleased
			};
			constexpr InputEvent(const Action &_action) : action{ _action } {}
			const Action action;

		protected:
		};

		class KeyPressedEvent : public InputEvent, public EventTemplate<KeyPressedEvent>
		{
		public:
			constexpr KeyPressedEvent(const input::Key key_) : InputEvent{ Action::KeyPressed }, key{ key_ } {}
			const input::Key key;
			virtual ~KeyPressedEvent() {}
		};

		class KeyReleasedEvent : public InputEvent, public EventTemplate<KeyPressedEvent>
		{
		public:
			constexpr KeyReleasedEvent(const input::Key key_) : InputEvent{ Action::KeyPressed }, key{ key_ } {}
			const input::Key key;
			virtual ~KeyReleasedEvent() {}
		};
	}
}

#endif
