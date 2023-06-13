#ifndef HAF_BACKEND_FACTORY_TYPES_INLUDE_HPP
#define HAF_BACKEND_FACTORY_TYPES_INLUDE_HPP

#include <backend_dev/include/ifactory.hpp>

namespace haf::backend
{
class IWindow;
}  // namespace haf::backend

namespace haf::backend
{
using IWindowFactory         = IFactoryOf<IWindow>;

}  // namespace haf::backend

#endif
