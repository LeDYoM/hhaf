#ifndef MTYPES_MENUM_INCLUDE_HPP
#define MTYPES_MENUM_INCLUDE_HPP

#include <type_traits>
#include <limits>

namespace mtps
{

template <typename T>
class MEnum
{
public:
    static_assert(std::is_enum_v<T>, "MEnum only works with enums");
    // requires T::min and T::max to be enum values.
    static constexpr auto min = T::min;
    static constexpr auto max = T::max;

    static constexpr auto min_numeric = static_cast<std::underlying_type_t<T>>(T::min);
    static constexpr auto max_numeric = static_cast<std::underlying_type_t<T>>(T::max);

    static constexpr auto min_str = to_str(T::min);
    static constexpr auto max_str = to_str(T::max);

    constexpr auto const toStr()
    {
        // Requires to_str(T) overload
        return to_str(value);
    }

    constexpr MEnum() noexcept = default;
    constexpr explicit MEnum(T val) noexcept : value{val} {}

    constexpr auto getNumeric() const noexcept
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }

    constexpr T getValue() const noexcept { return value; }

    constexpr MEnum &operator++() noexcept
    {
        value = static_cast<T>(
            static_cast<std::underlying_type_t<T>>(value) + 1);
        return *this;
    }

    constexpr MEnum &operator--() noexcept
    {
        value = static_cast<T>(
            static_cast<std::underlying_type_t<T>>(value) - 1);
        return *this;
    }

    constexpr bool isValid() const noexcept
    {
        return (getNumeric() >= min_numeric) &&
            (getNumeric() <= max_numeric);
    }

    constexpr bool nextIsValid() const noexcept
    {
        MEnum temp{value};
        return (++temp).isValid();
    }

    constexpr bool previousIsValid() const noexcept
    {
        MEnum temp{value};
        return (--temp).isValid();
    }
private:
    T value;
};

} // namespace mtps

#endif
