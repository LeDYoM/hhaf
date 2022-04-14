#ifndef HAF_SCENE_MATERIAL_INCLUDE_HPP
#define HAF_SCENE_MATERIAL_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/haf_export.hpp>

#include <htypes/include/str.hpp>

namespace haf::scene
{
struct MaterialBuffer
{
    htps::str name;
    htps::size_type size;
    htps::size_type packet_size;
};

class HAF_API Material
{

};
}  // namespace haf::scene

#endif
