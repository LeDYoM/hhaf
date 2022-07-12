#ifndef HLOG_COUT_COMMITER_INCLUDE_HPP
#define HLOG_COUT_COMMITER_INCLUDE_HPP

#include <logger/include/stream_commiter.hpp>
// Avoid dummy MSVC windows
#define __STDC_WANT_SECURE_LIB__ 1
#include <iostream>

namespace haf
{
struct COutCommiter : public logger::StreamCommiter<&(std::cout)>
{};

}  // namespace haf

#endif
