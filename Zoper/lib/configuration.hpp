#ifndef __LIB_CONFIGURATION_HPP__
#define __LIB_CONFIGURATION_HPP__

#include <string>
#include <map>
#include <fstream>
#include <functional>
#include <vector>
#include "types.hpp"

namespace lib
{
	class Configuration
	{
	public:
		Configuration() = delete;
		Configuration(const std::string &file);
		Configuration(const Configuration &other) = delete;

		virtual ~Configuration() {}

		Configuration &operator=(const Configuration &other) = delete;
		s32 getAsInt(const std::string &name) const;
		std::string getAsString(const std::string &name) const;

		typedef std::map<std::string, std::string> CMap;
		typedef std::pair<std::string, std::string> CMapLine;
		typedef std::map<std::string, CMap> CDataMap;

		std::string addConfigProperty(const std::string &name, const std::string &value, bool overwrite = false);
		s32 addConfigInt(const std::string &name, int value, bool overwrite = false);
		bool configFileExists(const std::string &file);

		void for_each_property(std::function<void(const CMapLine&)> callback);
	protected:
		std::vector<std::string> splitString(const std::string &input, const char separator);
	private:
		const std::string currentFile;
		CMap *currentMap;
		static CDataMap _data;
	};
}

#endif
