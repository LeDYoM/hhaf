#include <lib/shareddata/i_include/shareddata.hpp>

#include <lib/include/liblog.hpp>

namespace lib::shdata
{
SharedDataSystem::SharedDataSystem()
    : AppService{}, data_{nullptr} {}

SharedDataSystem::~SharedDataSystem() {}

void SharedDataSystem::store(uptr<IShareable> data)
{
    if (data_ != nullptr)
    {
        DisplayLog::warn("The stored data was not empty!");
    }
}

uptr<IShareable> SharedDataSystem::retrieve()
{
    return std::move(data_);
}

} // namespace lib::sys
