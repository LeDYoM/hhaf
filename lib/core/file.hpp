#pragma once

#ifndef LIB_FILE_INCLUDE_HPP__
#define LIB_FILE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>


namespace lib
{
	class File
	{
	public:
		File() = delete;
		File &operator=(const File &other) = delete;
		File(const File &other) = delete;
		File(str file);

		bool exists() const;
		string_vector readAsText();

		~File();
	private:
		str m_fileName;
	};

}

#endif
