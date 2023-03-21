#include <haf/include/shareddata/address.hpp>
#include <haf/include/core/types.hpp>
#include <htypes/include/object.hpp>
#include <utility>

namespace haf::shdata
{
struct Address::AddressPrivate
{
    AddressPrivate(core::str const& addr, char const separator) :
        address_parts_{addr.split(separator)}
    {}

    constexpr explicit AddressPrivate(AddressPrivate const& addr_private) :
        address_parts_{addr_private.address_parts_}
    {}

    ~AddressPrivate() = default;

    AddressPrivate(AddressPrivate&&) noexcept = default;
    AddressPrivate& operator=(AddressPrivate const&) noexcept = default;
    AddressPrivate& operator=(AddressPrivate&&) noexcept = default;

    core::vector<core::str> address_parts_;
};

Address::Address(core::str const& addr, char const separator) :
    private_{core::make_pimplp<AddressPrivate>(addr, separator)}
{}

Address::Address(core::str const& addr) :
    Address{addr, '/'}
{}

Address::Address(Address const& address) :
    private_{core::make_pimplp<AddressPrivate>(*(address.private_))}

{}

Address::~Address() = default;

Address& Address::operator=(Address const& address)
{
    Address tmp(address);
    std::swap(*this->private_, *(tmp.private_));
    return *this;
}

Address::Address(Address&& address) noexcept = default;
Address& Address::operator=(Address&& address) noexcept = default;

core::size_type Address::size() const noexcept
{
    return private_->address_parts_.size();
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

Address::reference Address::operator[](core::size_type const index) noexcept
{
    return private_->address_parts_[index];
}

Address::const_reference Address::operator[](
    core::size_type const index) const noexcept
{
    return private_->address_parts_[index];
}

core::str Address::first() const
{
    return private_->address_parts_[0U];
}

core::str Address::last() const
{
    return private_->address_parts_[private_->address_parts_.size() - 1U];
}

core::str Address::str() const
{
    if (!private_->address_parts_.empty())
    {
        core::str result{private_->address_parts_.size() * 10U};
        for (const auto part : private_->address_parts_)
        {
            result += part;
        }
        return result;
    }
    return "";
}

bool Address::isAbsolute() const noexcept
{
    return first().empty();
}

bool Address::isFinal() const noexcept
{
    return last().empty();
}

bool Address::removeFirst()
{
    if (private_->address_parts_.size() > 1U)
    {
        private_->address_parts_.erase_one_index<false>(0U);
        return true;
    }
    return false;
}

bool Address::removeLast()
{
    if (private_->address_parts_.size() > 1U)
    {
        private_->address_parts_.erase_one_index(
            private_->address_parts_.size() - 1U);
        return true;
    }
    return false;
}

core::pair<bool, htps::Object> objectFromAddress(Address const& address,
                                                 htps::Object const& object)
{
    if (address.isFinal())
    {
        htps::Object const* result{&object};
        core::size_type size{address.size()};

        core::size_type index_start{0U};
        if (address[0].empty())
        {
            index_start = 1U;
        }

        for (core::size_type index{index_start}; index < (size - 1U); ++index)
        {
            htps::Object::Value temp = result->getObject(address[index]);
            if (temp.isObject())
            {
                result = &(temp.getObject());
            }
            else
            {
                return {false, {}};
            }
        }

        return {true, *result};
    }

    return {false, {}};
}

htps::Object* ensureAddress(Address const& address, htps::Object& object)
{
    if (address.isFinal())
    {
        htps::Object* result{&object};
        core::size_type size{address.size()};

        core::size_type index_start{0U};
        if (address.first().empty())
        {
            index_start = 1U;
        }

        for (core::size_type index{index_start}; index < (size - 1U); ++index)
        {
            if (htps::Object * temp{result->acquireObject(address[index])};
                temp != nullptr)
            {
                result = temp;
            }
            else
            {
                result->set(address[index], htps::Object{});
                result = result->acquireObject(address[index]);
            }
        }

        return result;
    }

    return nullptr;
}

}  // namespace haf::shdata
