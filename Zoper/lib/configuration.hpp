#ifndef __LIB_CONFIGURATION_HPP__
#define __LIB_CONFIGURATION_HPP__

#include <string>
#include <map>
#include <fstream>
#include "types.hpp"

namespace lib
{
	class Configuration
	{
	public:
		Configuration() {}
		virtual ~Configuration() {}

		s32 getAsInt(const std::string &name) const;
		std::string getAsString(const std::string &name) const;

		typedef std::map < std::string, std::string > CMap;
		typedef std::pair<std::string, std::string> CMapLine;

		bool addConfigProperty(const std::string &name, const std::string &value);
		bool addConfigInt(const std::string &name, int value);
		bool addConfigFile(const std::string &fileName);

	private:
		static CMap _data;

	};

}

#endif
