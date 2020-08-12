#include "shareddatasystem.hpp"

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::sys
{
SharedDataSystem::~SharedDataSystem()
{
    makeEmpty();
}

bool SharedDataSystem::store(uptr<shdata::IShareable> data) noexcept
{
    if (data == nullptr)
    {
        DisplayLog::error("Trying to store an empty shareddata");
        return false;
    }

    if (data_ != nullptr)
    {
        DisplayLog::error("Shareddata must be empty before storing something");
        return false;
    }

    LogAsserter::log_assert(data_ == nullptr, "data_ is not nullptr");
    LogAsserter::log_assert(data != nullptr, "data is nullptr");

    // Aquire the ownership of data
    data_ = std::move(data);

    LogAsserter::log_assert(data_ != nullptr, "data_ is nullptr");
    LogAsserter::log_assert(data == nullptr, "data is not nullptr");

    return true;
}

uptr<shdata::IShareable> SharedDataSystem::retrieve() noexcept
{
    if (data_ == nullptr)
    {
        DisplayLog::error("Trying to retrieve empty shared data");
        return nullptr;
    }

    LogAsserter::log_assert(data_ != nullptr, "data_ is nullptr");
    uptr<shdata::IShareable> temp = std::move(data_);
    LogAsserter::log_assert(data_ == nullptr, "data_ is not nullptr");

    return temp;
}

bool SharedDataSystem::isEmpty() const noexcept
{
    return data_ == nullptr;
}

bool SharedDataSystem::makeEmpty()
{
    if (!isEmpty())
    {
        data_.reset();
        return true;
    }
    return false;
}

mtps::uptr<shdata::IShareable> const& SharedDataSystem::view() const noexcept
{
    LogAsserter::log_assert(data_ != nullptr, "data_ is nullptr");
    return data_;
}

}  // namespace haf::sys
