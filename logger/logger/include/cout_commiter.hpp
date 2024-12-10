#ifndef LOGGER_COUT_COMMITER_INCLUDE_HPP
#define LOGGER_COUT_COMMITER_INCLUDE_HPP

#include <logger/include/stream_commiter.hpp>
#include <iostream>

namespace logger
{
struct COutCommiter : public StreamCommiter<&(std::cout)>
{};

}  // namespace logger

#endif
