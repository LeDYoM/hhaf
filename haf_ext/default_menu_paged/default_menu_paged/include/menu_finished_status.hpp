#ifndef HAF_EXT_DEFAULT_MENU_PAGED_MENU_FINISHED_STATUS_INCLUDE_HPP
#define HAF_EXT_DEFAULT_MENU_PAGED_MENU_FINISHED_STATUS_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::exts::dmp
{
enum class MenuFinishedStatus : htps::u8
{
    Backward = 0U,
    Forward
};
}  // namespace haf::exts::dmp

#endif
