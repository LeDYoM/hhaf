#pragma once

#ifndef LIB_SERIALIZER_INCLUDE_HPP__
#define LIB_SERIALIZER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include "file.hpp"

namespace lib
{
	template <typename T>
	class Serializer
	{
	public:
		bool serialize(const str&fileName, T&data) {
			SerializationStreamOut sso;
			sso << data;
			FileOutput fout(fileName);
			return fout.write(sso.data());
		}

		bool deserialize(const str&fileName, T&data) {
			FileInput fin(fileName);
			if (fin.exists()) {
				auto ssi(fin.getAsStream());
				ssi >> data;
				return true;
			}
			return false;
		}

	};
}

#endif
