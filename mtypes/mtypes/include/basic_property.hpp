#ifndef MTPS_BASIC_PROPERTY_INCLUDE_HPP
#define MTPS_BASIC_PROPERTY_INCLUDE_HPP

#include "properties.hpp"

namespace mtps
{
template <typename T, typename Tag = DummyTag>
class BasicProperty : public IProperty<T, Tag>
{
public:
    using Base = IProperty<T, Tag>;
    using tag = typename Base::tag;
    using type = typename Base::type;
    using const_type = typename Base::const_type;
    using reference = typename Base::reference;
    using const_reference = typename Base::const_reference;
    using pointer = typename Base::pointer;
    using const_pointer = typename Base::const_pointer;

    constexpr BasicProperty() noexcept = default;
    ~BasicProperty() override = default;

    constexpr BasicProperty(BasicProperty &&) noexcept = default;
    BasicProperty(const BasicProperty &) = default;
    constexpr BasicProperty &operator=(BasicProperty &&) noexcept = default;
    constexpr BasicProperty &operator=(const BasicProperty &) noexcept = default;

    constexpr BasicProperty(T &&iv) noexcept : m_value{std::move(iv)} {}
    constexpr BasicProperty(const T &iv) noexcept : m_value{iv} {}

    constexpr const T &operator()() const noexcept { return m_value; }
    constexpr const T &operator=(const T &v) noexcept
    {
        set(v);
        return v;
    }
    inline const T &get() const noexcept override final { return m_value; }
    inline bool set(const T &v) override
    {
        if (!(m_value == v))
        {
            m_value = v;
            return true;
        }
        return false;
    }

    inline bool set(T &&v) override
    {
        if (!(m_value == std::forward<T>(v)))
        {
            m_value = std::move(v);
            return true;
        }
        return false;
    }

protected:
    T m_value{};
};
} // namespace mtps

#endif
