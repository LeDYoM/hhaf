#ifndef HLOG_COUT_COMMITER_INCLUDE_HPP
#define HLOG_COUT_COMMITER_INCLUDE_HPP

#include <logger/include/stream_commiter.hpp>
#include <iostream>

namespace haf
{
struct COutCommiter : public logger::StreamCommiter<&(std::cout)>
{};

}  // namespace haf

#endif
