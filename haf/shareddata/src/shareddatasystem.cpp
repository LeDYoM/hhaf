#include <haf/shareddata/i_include/shareddatasystem.hpp>

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::sys
{

SharedDataSystem::SharedDataSystem(sys::SystemProvider& system_provider) noexcept
    : AppService{system_provider}, data_{nullptr} {}

SharedDataSystem::~SharedDataSystem()
{
    data_.reset();
}

void SharedDataSystem::store(uptr<shdata::IShareable> data) noexcept
{
    log_assert(data_ == nullptr, "data_ is not nullptr");
    log_assert(data != nullptr, "data is nullptr");
    
    // Aquire the ownership of data
    data_ = std::move(data);

    log_assert(data_ != nullptr, "data_ is not nullptr");
    log_assert(data == nullptr, "data is not nullptr");
}

uptr<shdata::IShareable> SharedDataSystem::retrieve() noexcept
{
    log_assert(data_ != nullptr, "data_ is nullptr");
    uptr<shdata::IShareable> temp = std::move(data_);
    log_assert(data_ == nullptr, "data_ is not nullptr");

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

} // namespace haf::sys
