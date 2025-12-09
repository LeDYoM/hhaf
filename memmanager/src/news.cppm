module;

#include <cstddef>
#include <new>

export module memmanager:news;

import :funcs;

export void* operator new(std::size_t size)
{
    return memm::mmalloc(size);
}

export void* operator new(std::size_t size, std::nothrow_t const&) noexcept
{
    return memm::mmalloc(size);
}

export void* operator new[](std::size_t size)
{
    return memm::mmalloc(size);
}

export void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return memm::mmalloc(size);
}

export void operator delete(void* data) noexcept
{
    return memm::mfree(data);
}
