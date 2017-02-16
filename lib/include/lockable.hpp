#ifndef LIB_LOCKABLE_HPP__
#define LIB_LOCKABLE_HPP__

#include "types.hpp"

#pragma once

namespace lib
{
	class Lockable
	{
	public:
		inline bool locked() const noexcept { return m_lockCount > 0; }
		inline void lock()  noexcept { ++m_lockCount; }
		inline u32 lockCount() const  noexcept { return m_lockCount; }
		void unlock() noexcept {
			if (m_lockCount > 0) {
				--m_lockCount;
				if (!m_lockCount) {
					unlocked();
				}
			}
		}
		virtual void unlocked() noexcept = 0;
	private:
		u32 m_lockCount{};
	};

	class Lock
	{
	public:
		inline Lock(Lockable *const lockable) : m_lockable{ *lockable } { m_lockable.lock(); }
		inline ~Lock() { m_lockable.unlock(); }
	private:
		Lockable& m_lockable;
	};

}

#endif
