module;

#include <iostream>

export module logger:cout_commiter;

import :stream_commiter;

namespace logger
{
export struct COutCommiter : public StreamCommiter<&(std::cout)>
{};

}  // namespace logger
