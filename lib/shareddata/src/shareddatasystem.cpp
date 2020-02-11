#include <lib/shareddata/i_include/shareddatasystem.hpp>

#include <lib/include/liblog.hpp>

namespace lib::sys
{

SharedDataSystem::SharedDataSystem()
    : AppService{}, data_{nullptr} {}

SharedDataSystem::~SharedDataSystem() {}

void SharedDataSystem::store(uptr<shdata::IShareable> data)
{
    if (data_ != nullptr)
    {
        DisplayLog::warn("The stored data was not empty!");
    }
}

uptr<shdata::IShareable> SharedDataSystem::retrieve()
{
    return std::move(data_);
}

} // namespace lib::sys
