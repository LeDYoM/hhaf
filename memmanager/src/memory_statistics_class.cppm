module;

#include <cstddef>
#include <cstdint>

export module memmanager:statistics_class;

namespace memm
{
export struct MemoryStatistics
{
    std::uint64_t num_alloc{0U};
    std::uint64_t num_dealloc{0U};
    std::uint64_t bytes_alloc{0U};
    std::uint64_t bytes_dealloc{0U};

    MemoryStatistics& operator+=(MemoryStatistics const& rhs)
    {
        num_alloc += rhs.num_alloc;
        num_dealloc += rhs.num_dealloc;
        bytes_alloc += rhs.bytes_alloc;
        bytes_dealloc += rhs.bytes_dealloc;
        return *this;
    }
};

MemoryStatistics operator+(MemoryStatistics const& lhs,
                           MemoryStatistics const& rhs)
{
    return MemoryStatistics{
        .num_alloc{lhs.num_alloc + rhs.num_alloc},
        .num_dealloc{lhs.num_dealloc + rhs.num_dealloc},
        .bytes_alloc{lhs.bytes_alloc + rhs.bytes_alloc},
        .bytes_dealloc{lhs.bytes_dealloc + rhs.bytes_dealloc}};
}

}  // namespace memm
