#ifndef MTPS_HTYPES_RAWMEMORY_INCLUDE_HPP
#define MTPS_HTYPES_RAWMEMORY_INCLUDE_HPP

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
    using inner_type = std::byte;

    /// Default constructor.
    constexpr RawMemory() noexcept : data_{nullptr}, size_{0U} {}

    RawMemory(uptr<inner_type[]> data, size_type const size) :
        data_{std::move(data)}, size_{size}
    {}

    RawMemory(RawMemory const& rhs) :
        data_{uptr<inner_type[]>(new inner_type[rhs.size_])}, size_{rhs.size_}
    {
        std::memcpy(data_.get(), rhs.data_.get(), size_);
    }

    RawMemory(RawMemory&&) noexcept = default;
    RawMemory& operator=(RawMemory&&) noexcept = default;

    inner_type const* cbegin() const noexcept { return data_.get(); }
    inner_type const* cend() const noexcept
    {
        return data_.get() + size();
    }

    size_type size() const noexcept
    {
        return (data_ != nullptr) ? size_ : 0U;
    }

    bool empty() const noexcept { return size() == 0U; }

    inner_type const* data() const noexcept { return data_.get(); }

private:
    uptr<inner_type[]> data_;
    size_type size_;
};
}  // namespace htps

#endif
