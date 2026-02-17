export module haf:components:component_factory;

import :component;
import :utils_object_factory;

namespace haf::component
{
using ComponentFactory = utils::ObjectFactory<Component>;
}
