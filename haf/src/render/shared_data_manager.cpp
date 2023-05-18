#include <haf/include/render/shared_data_manager.hpp>
#include <hogl/include/types.hpp>

using namespace haf::core;

namespace haf::render
{
SharedDataManager::SharedDataManager()  = default;
SharedDataManager::~SharedDataManager() = default;

void SharedDataManager::init()
{}

bool SharedDataManager::add(str const& name,
                            sptr<SharedDataBuffer> sharedDataBuffer)
{
    return m_shared_data_buffers.add(name, core::move(sharedDataBuffer));
}

sptr<SharedDataBuffer> SharedDataManager::get(
    core::str const& name) const noexcept
{
    auto const iterator{m_shared_data_buffers.find(name)};
    return iterator == m_shared_data_buffers.end() ? nullptr : iterator->second;
}

}  // namespace haf::render
