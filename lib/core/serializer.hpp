#pragma once

#ifndef LIB_SERIALIZER_INCLUDE_HPP__
#define LIB_SERIALIZER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/include/core/log.hpp>

#include <lib/system/filesystem/file.hpp>

namespace lib
{
	template <typename T>
	class Serializer
	{
	public:
		constexpr bool serialize(const str&fileName, T&data) {
			SerializationStreamOut sso;
			sso << data;
			FileOutput fout{ fileName };
            //TO DO: Fix this nonsense.
			return fout.write(sso.data().split(','));
		}

		constexpr bool deserialize(const str&fileName, T&data) {
			FileInput fin{ fileName };
			if (fin.exists()) {
                SerializationStreamIn ssi(fin.getAsStream());
				ssi >> data;
				return true;
			}
			else {
				log_debug_info("File ", fileName, " cannot be opened for reading");
			}
			return false;
		}

	};
}

#endif
