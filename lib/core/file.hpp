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
		FileInput(str file)
			: m_fileName{ std::move(file) } {}

		bool exists() const;
		string_vector readAsText(const char_type separator = ',');
		SerializationStreamIn getAsStream(const char_type separator = ',');
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
		FileOutput &operator=(const FileOutput &other) = default;
		FileOutput(const FileOutput &other) = default;
		FileOutput &operator=(FileOutput &&other) = default;
		FileOutput(FileOutput &&other) = default;
		FileOutput(str file, const u32 maxLineSize = 80)
			: m_fileName{ std::move(file) }, m_maxLineSize{ maxLineSize } {}

		bool write(const string_vector &data, const char_type separator = ',');
		bool write(SerializationStreamOut data, const char_type separator = ',');
		~FileOutput() = default;
	private:
		u32 m_maxLineSize;
		str m_fileName;
	};

}

#endif
