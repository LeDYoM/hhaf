#pragma once

#ifndef LIB_RANDOMIZER_INCLUDE_HPP
#define LIB_RANDOMIZER_INCLUDE_HPP

#include <mtypes/include/types.hpp>

#include <lib/core/appservice.hpp>

namespace lib::core
{
    class Host;

	class Randomizer : public AppService
	{
	public:
		Randomizer(Host &host);
		~Randomizer() override;

		u32 getUInt(const size_type max = 1U, const size_type min = 0U) const;
	private:
        class RandomizerPrivate;
		uptr<RandomizerPrivate> p_rPriv;
	};
}

#endif
