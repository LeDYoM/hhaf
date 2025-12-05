module;

#include <cstdint>

export module memmanager:bytes;

struct Bytes
{
    uint64_t bytes;

    constexpr uint64_t KBytes() const noexcept { return bytes / 1024U; }

    constexpr uint64_t MBytes() const noexcept
    {
        return bytes / (1024U * 1024U);
    }

    constexpr uint64_t GBytes() const noexcept
    {
        return bytes / (1024U * 1024U * 1024U);
    }
};
