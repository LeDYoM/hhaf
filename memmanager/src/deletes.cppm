module;

export module memmanager:deletes;

export void operator delete(void* data, const std::nothrow_t&) noexcept
{
    return memm::mfree(data);
}

export void operator delete(void* data, std::size_t size)
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
