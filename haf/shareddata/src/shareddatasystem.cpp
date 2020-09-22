#include "shareddatasystem.hpp"
#include <haf/shareddata/include/address.hpp>

#include <hlog/include/hlog.hpp>

#include <utility>

using namespace mtps;

namespace haf::sys
{
SharedDataSystem::~SharedDataSystem() = default;

bool SharedDataSystem::store(uptr<shdata::IShareable> data) noexcept
{
    LogAsserter::log_assert(data != nullptr, "data is nullptr");

    LogAsserter::log_assert(data == nullptr, "data is not nullptr");

    return true;
}

uptr<shdata::IShareable> SharedDataSystem::retrieve() noexcept
{
}

bool SharedDataSystem::isEmpty() const noexcept
{
    return data_object_.empty();
}

bool SharedDataSystem::makeEmpty()
{
    if (!isEmpty())
    {
        data_object_ = Object{};
        return true;
    }
    return false;
}

mtps::uptr<shdata::IShareable> const& SharedDataSystem::view() const noexcept
{
}

bool SharedDataSystem::store(shdata::Address const& address,
                             shdata::IShareable const& data)
{
    Object temp;

    bool const result{data.serialize(temp)};
    if (result)
    {
        auto result_apply_address =
            shdata::objectFromAddress(address, data_object_);

        if (result_apply_address.first)
        {
            std::swap(data_object_, temp);
            return true;
        }
    }

    return false;
}

bool SharedDataSystem::createIfNecessary(shdata::Address const& address)
{
    auto result_apply_address =
        shdata::objectFromAddress(address, data_object_);

    if (!result_apply_address.first)
    {
        
    }

}

bool SharedDataSystem::retrieve(shdata::Address const& address,
                                shdata::IShareable& data)
{
    auto result_apply_address =
        shdata::objectFromAddress(address, data_object_);

    if (result_apply_address.first)
    {
        return data.deserialize(result_apply_address.second);
    }

    return false;
}

}  // namespace haf::sys
