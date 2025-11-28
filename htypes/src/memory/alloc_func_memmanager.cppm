module;

//#include <memmanager/include/memmanager.hpp>
#include "../../../memmanager/memmanager/include/memmanager.hpp"

export module htypes:alloc_func_memmanager;

import :allocatorfunc;

namespace htps
{

template <typename T>
using AllocatorMemManagerRaw =
    htps::AllocatorFunc<T, mmalloc, mfree, mfree_with_size>;

}  // namespace htps
