HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_BUFFER_OBJECT_CONSTRUCTION_PARAMS_INCLUDE_HPP
#define HAF_RENDER_BUFFER_OBJECT_CONSTRUCTION_PARAMS_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>

namespace haf::render
{
struct BufferObjectUnsizedConstructParams
{
    const void* const data;
    core::s32 const dataSize;
    BufferUsage const bufferUsage;
    BufferMode const bufferMode;
    BufferSubObject vertexFormat;
};

struct BufferObjectConstructParams : BufferObjectUnsizedConstructParams
{
    core::u32 const size;
};

}  // namespace haf::render

#endif
