module;

#include <new>

export module memmanager : deletes;

import : funcs;

export void operator delete(void* data, std::nothrow_t const&) noexcept
{
    memm::mfree(data);
}

export void operator delete(void* data, std::size_t const size)
{
    memm::mfree_with_size(data, size);
}

export void operator delete(void* data,
                            std::size_t size,
                            const std::nothrow_t&) noexcept
{
    memm::mfree_with_size(data, size);
}

export void operator delete[](void* data, std::size_t size) noexcept
{
    memm::mfree_with_size(data, size);
}

export void operator delete[](void* data,
                              std::size_t size,
                              const std::nothrow_t&) noexcept
{
    memm::mfree_with_size(data, size);
}

export void operator delete[](void* data, std::align_val_t) noexcept
{
    memm::mfree(data);
}

export void operator delete[](void* data, const std::nothrow_t&) noexcept
{
    memm::mfree(data);
}

export void operator delete[](void* data) noexcept
{
    memm::mfree(data);
}
