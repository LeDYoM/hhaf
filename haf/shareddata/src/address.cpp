#include "address.hpp"
#include <mtypes/include/vector.hpp>

#include <utility>

using namespace mtps;

namespace haf::shdata
{
struct Address::AddressPrivate
{
    AddressPrivate(str const& addr, char const separator) :
        address_parts_(addr.split(separator))
    {}

    constexpr explicit AddressPrivate(AddressPrivate const& addr_private) :
        address_parts_(addr_private.address_parts_)
    {}

    vector<str> address_parts_;
};

Address::Address(str const& addr, char const separator) :
    private_{make_pimplp<AddressPrivate>(addr, separator)}
{}

Address::Address(Address const& address) :
    private_{make_pimplp<AddressPrivate>(*(address.private_))}

{}

Address::~Address() = default;

Address& Address::operator=(Address const& address)
{
    Address tmp(address);
    std::swap(*this, tmp);
    return *this;
}

size_type Address::size() const noexcept
{
    return private_->address_parts_.size();
}

bool Address::empty() const noexcept
{
    return private_->address_parts_.empty();
}

Address::iterator Address::begin() noexcept
{
    return private_->address_parts_.begin();
}

Address::iterator Address::end() noexcept
{
    return private_->address_parts_.end();
}

Address::const_iterator Address::begin() const noexcept
{
    return private_->address_parts_.begin();
}

Address::const_iterator Address::end() const noexcept
{
    return private_->address_parts_.end();
}

Address::reference Address::operator[](mtps::size_type const index) noexcept
{
    return private_->address_parts_[index];
}

Address::const_reference Address::operator[](
    mtps::size_type const index) const noexcept
{
    return private_->address_parts_[index];
}

str Address::first() const
{
    if (!private_->address_parts_.empty())
    {
        return private_->address_parts_[0U];
    }
    return "";
}

str Address::last() const
{
    if (!private_->address_parts_.empty())
    {
        return private_->address_parts_[private_->address_parts_.size() - 1U];
    }
    return "";
}

pair<bool, mtps::Object> applyAddress(Address const& address,
                                      Object const& object)
{
    Object result;

    for (auto it = address.cbegin(); it != address.cend(); ++it)
    {
        
    }

    return {true, Object{}};
}

}  // namespace haf::shdata
