#ifndef __LIB_HASNAME_HPP__
#define __LIB_HASNAME_HPP__

#include <string>

namespace lib
{
	namespace core
	{
		class HasName
		{
		public:
			HasName(std::string name) noexcept : m_name{ std::move(name) } {}
			constexpr HasName(HasName &&other)  noexcept = default;
			constexpr HasName(const HasName &other) = default;
			HasName &operator=(HasName &&other)  noexcept = default;
			HasName &operator=(const HasName &other) = default;
			virtual ~HasName() = default;
			
			virtual const std::string name() const noexcept { return m_name; }
		private:
			const std::string m_name;
		};
	}
}

#endif
