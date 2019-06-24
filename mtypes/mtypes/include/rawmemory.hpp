#pragma once

#ifndef LIB_MTYPES_RAWMEMORY_INCLUDE_HPP
#define LIB_MTYPES_RAWMEMORY_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib
{
    class RawMemory
    {
    public:
        constexpr RawMemory() noexcept : data_{ nullptr }, size_{ 0U } {}

        RawMemory(uptr<std::byte[]> data, const size_type size)
            : data_{ std::move(data) }, size_{ size } {}

        RawMemory(const RawMemory& rhs)
            : data_{ uptr<std::byte[]>(new std::byte[rhs.size_]) },
            size_{rhs.size_}
        {
            std::memcpy(data_.get(), rhs.data_.get(), size_);
        }

        RawMemory(RawMemory&&) noexcept = default;
        RawMemory& operator=(RawMemory&&) noexcept = default;

        constexpr size_type size() const noexcept { return (data_ != nullptr) ? size_ : 0U; }
        const void* data() const noexcept { return data_.get(); }

    private:
        uptr<std::byte[]> data_;
        size_type size_;
    };
}

#endif
