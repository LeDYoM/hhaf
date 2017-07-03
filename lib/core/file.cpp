#include "file.hpp"
#include <mtypes/include/log.hpp>
#include <fstream>

namespace lib
{
	File::File(str file) : m_fileName{ std::move(file) }
	{
	}
	bool File::exists() const
	{
		std::ifstream infile(m_fileName.c_str());
		return infile.good();
	}

	string_vector File::readAsText()
	{
		std::ifstream infile(m_fileName.c_str());
		if (infile.good() && infile.is_open()) {
			string_vector result;
			while (infile) {
				std::string line;
				infile >> line;
				if (!line.empty()) {
					result.emplace_back(std::move(line));
				}
			}
			return result;
		}
		else {
			log_debug_error("The file ", m_fileName, " does not exist");
		}

		return string_vector{};
	}

	File::~File()
	{
	}
}
