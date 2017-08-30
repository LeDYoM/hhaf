#pragma once

#ifndef LIB_FILE_INCLUDE_HPP__
#define LIB_FILE_INCLUDE_HPP__

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
		FileInput &operator=(const FileInput &other) = default;
		FileInput(const FileInput &other) = default;
		FileInput &operator=(FileInput &&other) = default;
		FileInput(FileInput &&other) = default;
		FileInput(str file, const char_type separator=',')
			: m_fileName{ std::move(file) }, m_separator{ separator } {}

		bool exists() const;
		string_vector readAsText();
		SerializationStreamIn getAsStream();

		~FileInput() = default;
	private:
		char_type m_separator;
		str m_fileName;
	};

	class FileOutput
	{
	public:
		using char_type = char;
		FileOutput() = delete;
		FileOutput &operator=(const FileOutput &other) = default;
		FileOutput(const FileOutput &other) = default;
		FileOutput &operator=(FileOutput &&other) = default;
		FileOutput(FileOutput &&other) = default;
		FileOutput(str file, const char_type separator = ',', const u32 maxLineSize = 80)
			: m_fileName{ std::move(file) }, m_separator{ separator }, m_maxLineSize{ maxLineSize } {}

		bool write(const string_vector &data);
		bool write(SerializationStreamOut data);
		~FileOutput() = default;
	private:
		char_type m_separator;
		u32 m_maxLineSize;
		str m_fileName;
	};

}

#endif
