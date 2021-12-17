#include "shared_data_system.hpp"
#include <haf/include/shareddata/address.hpp>

#include <hlog/include/hlog.hpp>

#include <utility>

using namespace htps;
using namespace haf::shdata;

namespace haf::sys
{
SharedDataSystem::~SharedDataSystem() = default;

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

bool SharedDataSystem::store(Address const& address, IShareable const& data)
{
    if (address.isFinal())
    {
        Object temp;

        auto* result_ensure_address = ensureAddress(address, data_object_);

        if (result_ensure_address != nullptr)
        {
            bool const result{data.serialize(temp)};
            if (result)
            {
                std::swap(*result_ensure_address, temp);
                return true;
            }
        }
    }

    return false;
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
