#include <haf/shareddata/include/address.hpp>
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

    ~AddressPrivate() = default;

    AddressPrivate(AddressPrivate&&) noexcept = default;
    AddressPrivate& operator=(AddressPrivate const&) noexcept = default;
    AddressPrivate& operator=(AddressPrivate&&) noexcept = default;

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
    std::swap(*this->private_, *(tmp.private_));
    return *this;
}

Address::Address(Address&& address) noexcept = default;
Address& Address::operator=(Address&& address) noexcept = default;

size_type Address::size() const noexcept
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
    return private_->address_parts_[0U];
}

str Address::last() const
{
    return private_->address_parts_[private_->address_parts_.size() - 1U];
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
        private_->address_parts_.erase_one_index(0U, false);
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

pair<bool, mtps::Object> objectFromAddress(Address const& address,
                                           Object const& object)
{
    if (address.isFinal())
    {
        Object const* result{&object};
        size_type size{address.size()};

        size_type index_start{0U};
        if (address[0].empty())
        {
            index_start = 1U;
        }

        for (size_type index{index_start}; index < (size - 1U); ++index)
        {
            Object::Value temp = result->getObject(address[index]);
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

mtps::Object* ensureAddress(Address const& address, mtps::Object& object)
{
    if (address.isFinal())
    {
        Object * result{&object};
        size_type size{address.size()};

        size_type index_start{0U};
        if (address.first().empty())
        {
            index_start = 1U;
        }

        for (size_type index{index_start}; index < (size - 1U); ++index)
        {
            Object* temp = result->acquireObject(address[index]);
            if (temp != nullptr)
            {
                result = temp;
            }
            else
            {
                result->set(address[index], Object{});
                result = result->acquireObject(address[index]);
            }
        }

        return result;
    }

    return nullptr;
}

}  // namespace haf::shdata
