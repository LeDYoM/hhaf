#ifndef HAF_SCENE_IDATA_WRAPPER_INCLUDE_HPP
#define HAF_SCENE_IDATA_WRAPPER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/utils/attachable.hpp>

namespace haf::sys
{
class SystemAccess;
}

namespace haf::sys
{

/**
 * @brief Base class for classes that provide some kind of access to specific
 *  data.
 * The idea is that when an scene node needs access to specific data it wraps
 * it in some subclass of this class that will bring getters and setter to
 * some specific data via a scene node.
 * The @b IDataWrapper is not stored anywhere internally.
 */
class IDataWrapper : public utils::Attachable<sys::SystemAccess>
{
public:
    /**
     * @brief Public type alias template with the acched node type of this
     * attachable. Required from @b sys::Atachable
     */
    using AttachedNodeType =
        utils::Attachable<sys::SystemAccess>::AttachedNodeType;

private:
    friend class DataWrapperCreator;
};
}  // namespace haf::sys

#endif
