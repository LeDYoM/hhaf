#include "file.hpp"
#include <mtypes/include/log.hpp>
#include <fstream>
#include <string>

namespace lib
{
	bool FileInput::exists() const
	{
		std::ifstream infile(m_fileName.c_str());
		return infile.good();
	}

	string_vector FileInput::readAsText()
	{
		std::ifstream infile(m_fileName.c_str());
		if (infile.good() && infile.is_open()) {
			string_vector result;
			while (infile) {
				std::string line;
				infile >> line;
				if (!line.empty()) {
					result.emplace_back(line.c_str());
				}
			}
			return result;
		}
		else {
			log_debug_error("The file ", m_fileName, " does not exist");
		}

		return string_vector{};
	}

	SerializationStreamOut FileInput::getAsStream()
	{
		auto data(readAsText());
		return SerializationStreamOut();
	}

	bool FileOutput::write(const string_vector & data)
	{
		std::ofstream outfile(m_fileName.c_str());
		if (outfile.good() && outfile.is_open()) {
			for (auto&& line : data) {
				outfile << line.c_str() << "\n";
			}
			return true;
		}
		else {
			log_debug_error("The file ", m_fileName, " cannot be open");
		}

		return false;
	}
}
