#pragma once

#ifndef HAF_SHAREDDATA_ADRESS_INCLUDE_HPP
#define HAF_SHAREDDATA_ADRESS_INCLUDE_HPP

#include <mtypes/include/p_impl_pointer.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/object.hpp>
#include <haf/haf_export.hpp>

namespace haf::shdata
{
/**
 * @brief Class to encapsulate an address comming from an string and a separator
 */
class HAF_API Address
{
public:
    using iterator        = mtps::str*;
    using const_iterator  = mtps::str const*;
    using reference       = mtps::str&;
    using const_reference = mtps::str const&;

    /**
     * @brief Construct a new Address object
     *
     * @param addr string containing the complete addres to parse
     * @param separator Element to be used as a separator of the parts of the
     *  address.
     */
    Address(mtps::str const& addr, char const separator = '/');

    /**
     * @brief Construct a new Address object.
     * Explicit copy constructor.
     *
     * @param address Source address to copy from.
     */
    explicit Address(Address const& address);

    /**
     * @brief Destroy the Address object
     */
    ~Address();

    /**
     * @brief Construct a new Address object moving from another one
     *
     * @param address Source address
     */
    Address(Address&& address) noexcept = default;

    /**
     * @brief Copy assignment
     *
     * @param address Source address
     * @return Address& Updated address
     */
    Address& operator=(Address const& address);

    /**
     * @brief Move assignment
     *
     * @param address Source address
     * @return Address& Updated address
     */
    Address& operator=(Address&& address) noexcept = default;

    mtps::size_type size() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    inline const_iterator cbegin() const noexcept { return begin(); }
    inline const_iterator cend() const noexcept { return end(); }

    reference operator[](mtps::size_type const index) noexcept;
    const_reference operator[](mtps::size_type const index) const noexcept;

    mtps::str first() const;
    mtps::str last() const;

    /**
     * @brief Check if an address is relative (it does not start with separator)
     * 
     * @return true If the address is not empty AND starts with a separator
     * @return false Otherwise
     */
    bool isAbsolute() const noexcept;

    /**
     * @brief Check if an address is final (it ends with separator)
     * 
     * @return true If the address is not empty AND ends with a separator
     * @return false Otherwise
     */
    bool isFinal() const noexcept;

    /**
     * @brief Opposite of isAbsolute()
     * @see isAbsolute
     * 
     * @return true  not absolute
     * @return false absolute
     */
    inline bool isRelative() const noexcept { return !isAbsolute(); }

    /**
     * @brief Opposite of isFinal()
     * @see isFinal
     * 
     * @return true not relative
     * @return false relative
     */
    inline bool isNotFinal() const noexcept { return !isFinal(); }

    bool removeFirst();
    bool removeLast();

private:
    struct AddressPrivate;
    mtps::PImplPointer<AddressPrivate> private_;
};

mtps::pair<bool, mtps::Object> objectFromAddress(Address const& address,
                                            mtps::Object const& object);

mtps::Object *ensureAddress(Address const& address, mtps::Object& object);

}  // namespace haf::shdata

#endif
