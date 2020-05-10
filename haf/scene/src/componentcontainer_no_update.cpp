#include "componentcontainer.hpp"

#include <hlog/include/hlog.hpp>
#include <mtypes/include/algoutils.hpp>

using namespace mtps;

namespace haf::scene
{
template <>
void ComponentContainerPart<false>::updateComponents()
{
    components_.update();
}

}  // namespace haf::scene
