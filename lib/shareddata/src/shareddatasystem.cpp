#include <lib/shareddata/i_include/shareddatasystem.hpp>

#include <lib/include/liblog.hpp>

namespace lib::sys
{

SharedDataSystem::SharedDataSystem()
    : AppService{}, data_{nullptr} {}

SharedDataSystem::~SharedDataSystem()
{
    data_.reset();
}

void SharedDataSystem::store(uptr<shdata::IShareable> data)
{
    log_assert(data_ == nullptr, "data_ is not nullptr");
    log_assert(data != nullptr, "data is nullptr");
    
    // Aquire the ownership of data
    data_ = std::move(data);

    log_assert(data_ != nullptr, "data_ is not nullptr");
    log_assert(data == nullptr, "data is not nullptr");
}

uptr<shdata::IShareable> SharedDataSystem::retrieve()
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

} // namespace lib::sys
