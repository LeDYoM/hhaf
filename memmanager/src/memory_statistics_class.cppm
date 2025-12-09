module;

#include <cstddef>
#include <cstdint>

export module memmanager:statistics_class;

namespace memm
{
export struct MemoryStatistics
{
    std::uint64_t num_alloc_{0U};
    std::uint64_t num_dealloc_{0U};
    std::uint64_t bytes_alloc_{0U};
    std::uint64_t bytes_dealloc_{0U};
};

}  // namespace memm
