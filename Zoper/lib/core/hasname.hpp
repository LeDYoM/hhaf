#ifndef __LIB_IHASNAME_HPP__
#define __LIB_IHASNAME_HPP__

#include <string>
#include "../compileconfig.hpp"

namespace lib
{
	namespace core
	{
		class IHasName
		{
		public:
			IHasName() {}
			virtual ~IHasName() {}

			virtual const std::string name() const = 0;
		};

		class HasName
		{
		public:
			HasName(const std::string name) :_name(name) {}
			virtual ~HasName() {}
			
			virtual const std::string name() const { return _name; }
		private:
			std::string _name;
		};
	}
}

#endif
