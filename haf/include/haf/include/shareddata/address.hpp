#ifndef HAF_SHAREDDATA_ADRESS_INCLUDE_HPP
#define HAF_SHAREDDATA_ADRESS_INCLUDE_HPP

#include <htypes/include/p_impl_pointer.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/object.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::shdata
{
/**
 * @brief Class to encapsulate an address coming from an string and a separator
 */
class HAF_API Address
{
public:
    using iterator        = htps::str*;
    using const_iterator  = htps::str const*;
    using reference       = htps::str&;
    using const_reference = htps::str const&;

    /**
     * @brief Construct a new Address object
     *
     * @param addr string containing the complete addres to parse
     * @param separator Element to be used as a separator of the parts of the
     *  address.
     */
    Address(htps::str const& addr, char const separator = '/');

    /**
     * @brief Destroy the Address object
     */
    ~Address();

    /**
     * @brief Construct a new Address object.
     * Explicit copy constructor.
     *
     * @param address Source address to copy from.
     */
    Address(Address const& address);

    /**
     * @brief Construct a new Address object moving from another one
     *
     * @param address Source address
     */
    Address(Address&& address) noexcept;

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
    Address& operator=(Address&& address) noexcept;

    htps::size_type size() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    inline const_iterator cbegin() const noexcept { return begin(); }
    inline const_iterator cend() const noexcept { return end(); }

    reference operator[](htps::size_type const index) noexcept;
    const_reference operator[](htps::size_type const index) const noexcept;

    htps::str first() const;
    htps::str last() const;

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
    htps::PImplPointer<AddressPrivate> private_;
};

/**
 * @brief Get a copy of an @b htps::Object contained at that address
 * 
 * @param address Address to retrieve
 * @param object Object where to search
 * @return htps::pair<bool, htps::Object> In the returned pair, the first
 * will be if the operation wass successful and the second will be an
 * @b htps::Object . If first is false, the second value is undefined.
 */
htps::pair<bool, htps::Object> objectFromAddress(Address const& address,
                                            htps::Object const& object);

/**
 * @brief Check that an @b Address exists in an @b htps::Object and retrieve
 * a pointer to the element. Otherwhise, create the structure inside the
 * @b htps::Object and return a pointer to the newly created @b htps::Object
 * too.
 * @param address Adress to search for
 * @param object Object where to search
 * @return htps::Object* Pointer to the old or new Object. Might be nullptr if
 * for any reason it cannot be created.
 */
htps::Object *ensureAddress(Address const& address, htps::Object& object);

}  // namespace haf::shdata

#endif
