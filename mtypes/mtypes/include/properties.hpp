#ifndef MTPS_PROPERTIES_INCLUDE_HPP
#define MTPS_PROPERTIES_INCLUDE_HPP

namespace mtps
{
struct DummyTag {};

/**
 * @brief Class provides a basic interface for properties. This is the base
 * class for any Property class.
 * @tparam T Inner type of the property.
 */
template <typename T, typename Tag>
class IProperty
{
public:
    using tag = Tag;
    using type = T;
    using const_type = T const;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const *;

    /**
     * @brief Get value of the property.
     * @return const T& The content of the property.
     */
    virtual const T &get() const noexcept = 0;

    /**
     * @brief Sets the vañue of the inner type of the property.
     * 
     * @param v New value to set.
     * @return true The value has changed
     * @return false v was equal to the content, so no changes made.
     */
    virtual bool set(const T &v) = 0;
    virtual bool set(T &&v) = 0;
};

} // namespace mtps

#endif
