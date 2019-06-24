#include "file.hpp"

#include <lib/include/liblog.hpp>

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
        string_vector result;
        std::ifstream infile(m_fileName.c_str());
		if (infile.good() && infile.is_open()) 
        {
			while (infile) 
            {
				std::string line;
				infile >> line;
				result.emplace_back(line.c_str());
			}
		}
		else 
        {
			log_debug_error("The file ", m_fileName, " does not exist");
		}

        return result;
    }

	SerializationStreamIn FileInput::getAsStream()
	{
		return SerializationStreamIn(readAsText());
	}

	vector<char> FileInput::readBinary()
	{
		std::ifstream is(m_fileName.c_str(), std::ios::binary);
		if (is) {
			auto fl(fileLength());
			vector<char> result(fl);
			is.read(&(result[0]), fl);
			return result;
		}

		return vector<char>();
	}

	u32 FileInput::fileLength()
	{
		std::ifstream is(m_fileName.c_str(), std::ios::binary);
		if (is) {
			is.seekg(0, std::ios::end);
			return static_cast<u32>(is.tellg());
		}
		return 0;
	}

	bool FileOutput::write(const string_vector & data, const char_type separator)
	{
		std::ofstream outfile(m_fileName.c_str());
		if (outfile.good() && outfile.is_open()) {
			for (auto&& line : data) {
				outfile << (line.empty()?"":line.c_str());
				if (&line != std::prev(data.end())) {
					outfile << separator;
				}
			}
			return true;
		}
		else {
			log_debug_error("The file ", m_fileName, " cannot be open");
		}

		return false;
	}

	bool FileOutput::write(const SerializationStreamOut data, const char_type separator)
	{
        return write(string_vector{ data.data() }, separator);
	}
}
