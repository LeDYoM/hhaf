#ifndef MTPS_MTYPES_RAWMEMORY_INCLUDE_HPP
#define MTPS_MTYPES_RAWMEMORY_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <cstring>

namespace htps
{
/**
     * @brief Class wrapping a unique pointer to an array of bytes.
     * This class wraps and owns an array of bytes. Instances are
     * copyable and cheaply movable. A size is maintained.
     */
class RawMemory
{
public:
    /// Default constructor.
    constexpr RawMemory() noexcept : data_{nullptr}, size_{0U} {}

    RawMemory(uptr<std::byte[]> data, const size_type size)
        : data_{std::move(data)}, size_{size} {}

    RawMemory(const RawMemory &rhs)
        : data_{uptr<std::byte[]>(new std::byte[rhs.size_])},
          size_{rhs.size_}
    {
        std::memcpy(data_.get(), rhs.data_.get(), size_);
    }

    RawMemory(RawMemory &&) noexcept = default;
    RawMemory &operator=(RawMemory &&) noexcept = default;

    inline size_type size() const noexcept { return (data_ != nullptr) ? size_ : 0U; }
    const std::byte *data() const noexcept { return data_.get(); }

private:
    uptr<std::byte[]> data_;
    size_type size_;
};
} // namespace htps

#endif
