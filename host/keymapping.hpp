#ifndef __KEYMAPPING_HPP__
#define __KEYMAPPING_HPP__

#include <lib/core/configuration.hpp>
#include <lib/core/iuserproperties.hpp>
#include <lib/include/key.hpp>
#include "direction.hpp"
#include <array>

namespace zoper
{
	class KeyMapping : public lib::IUserProperties
	{
	public:
		KeyMapping();
		virtual ~KeyMapping();

		void setProperties(lib::Configuration &config) override;
		static const lib::u32 TotalKeys = Direction::Total + 2;

		lib::input::Key getKey(const Direction d) const;
		Direction getDirectionFromKey(const lib::input::Key k) const;
		lib::input::Key getLaunchKey() const;
		bool isLaunchKey(const lib::input::Key key) const;
		lib::input::Key getPauseKey() const;
		bool isPauseKey(const lib::input::Key key) const;

		bool setKey(const lib::u32 index, const lib::input::Key key);
		void apply();
	private:
		std::array<lib::input::Key, KeyMapping::TotalKeys> m_keys;
	};
}

#endif