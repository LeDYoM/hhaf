#pragma once

#ifndef LIB_FILE_INCLUDE_HPP
#define LIB_FILE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/streams.hpp>

namespace lib
{
	class FileInput
	{
	public:
		using char_type = char;
		FileInput() = delete;
		FileInput(str file)
			: m_fileName{ std::move(file) } {}

		bool exists() const;
		string_vector readAsText();
		SerializationStreamIn getAsStream();
		vector<char> readBinary();

		u32 fileLength();

		~FileInput() = default;
	private:
		str m_fileName;
	};

	class FileOutput
	{
	public:
		using char_type = char;
		FileOutput() = delete;
		FileOutput(str file, const u32 maxLineSize = 80)
			: m_fileName{ std::move(file) }, m_maxLineSize{ maxLineSize } {}

		bool write(const string_vector &data, const char_type separator = ',');
		bool write(SerializationStreamOut data, const char_type separator = ',');
		~FileOutput() = default;
	private:
		str m_fileName;
		u32 m_maxLineSize;
	};
}

#endif
