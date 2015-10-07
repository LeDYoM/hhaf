#ifndef __LIB_IHASNAME_HPP__
#define __LIB_IHASNAME_HPP__

#include <string>
#include "../compileconfig.hpp"

namespace lib
{
	namespace core
	{
		class HasName
		{
		public:
			HasName(const std::string name) :_name(name) {}
			virtual ~HasName() {}
			
			inline const std::string &name() const { return _name; }
		private:
			std::string _name;
		};
	}
}

#endif
