HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_SHARED_DATA_BUFFER_MANAGER_INCLUDE_HPP
#define HAF_RENDER_SHARED_DATA_BUFFER_MANAGER_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <haf/include/render/shared_data_buffer.hpp>

namespace haf::render
{
class HAF_PRIVATE SharedDataManager final
{
public:
    SharedDataManager();
    ~SharedDataManager();

    void init();

    bool add(core::str const& name,
             core::sptr<SharedDataBuffer> sharedDataBuffer);
    core::sptr<SharedDataBuffer> get(core::str const& name) const noexcept;

private:
    core::Dictionary<core::sptr<SharedDataBuffer>> m_shared_data_buffers;
};
}  // namespace haf::render

#endif
