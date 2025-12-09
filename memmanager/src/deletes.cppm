module;

#include <new>

export module memmanager:deletes;

import :funcs;

export void operator delete(void* data, std::nothrow_t const&) noexcept
{
    return memm::mfree(data);
}

export void operator delete(void* data, std::size_t const size)
{
    return memm::mfree_with_size(data, size);
}

export void operator delete(void* data,
                            std::size_t size,
                            const std::nothrow_t&) noexcept
{
    return memm::mfree_with_size(data, size);
}

export void operator delete[](void* data)
{
    return memm::mfree(data);
}

export void operator delete[](void* data, std::size_t size)
{
    return memm::mfree_with_size(data, size);
}

export void operator delete[](void* data, const std::nothrow_t&) noexcept
{
    return memm::mfree(data);
}

export void operator delete[](void* data,
                              std::size_t size,
                              const std::nothrow_t&) noexcept
{
    return memm::mfree_with_size(data, size);
}
