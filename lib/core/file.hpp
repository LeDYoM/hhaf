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
		FileInput() = delete;
		FileInput &operator=(const FileInput &other) = default;
		FileInput(const FileInput &other) = default;
		FileInput &operator=(FileInput &&other) = default;
		FileInput(FileInput &&other) = default;
		FileInput(str file) : m_fileName{ std::move(file) } {}

		bool exists() const;
		string_vector readAsText();
		SerializationStreamOut getAsStream();

		~FileInput() = default;
	private:
		str m_fileName;
	};

	class FileOutput
	{
		FileOutput() = delete;
		FileOutput &operator=(const FileOutput &other) = default;
		FileOutput(const FileOutput &other) = default;
		FileOutput &operator=(FileOutput &&other) = default;
		FileOutput(FileOutput &&other) = default;
		FileOutput(str file) : m_fileName{ std::move(file) } {}

		bool write(const string_vector &data);
		~FileOutput() = default;
	private:
		str m_fileName;
	};

}

#endif
