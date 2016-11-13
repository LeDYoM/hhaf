#ifndef LIB_CONSTSTRING_INCLUDE_HPP__
#define LIB_CONSTSTRING_INCLUDE_HPP__

namespace lib
{
#include <cstddef>
#include <stdexcept>

class str_const {
    const char * const p_;
    const std::size_t sz_;
public:
    template <std::size_t N>
    constexpr str_const( const char( & a )[ N ] )
		: p_( a ), sz_( N - 1 ) {}

    constexpr char operator[]( std::size_t n ) const 
	{
        return n < sz_ ? p_[ n ] : throw std::out_of_range( "" );
    }
    constexpr std::size_t size() const  noexcept { return sz_; }
};}

#endif
