#ifndef ZOPER_COMMON_SCENE_NODES_INCLUDE_HPP
#define ZOPER_COMMON_SCENE_NODES_INCLUDE_HPP

#include <haf/render/include/renderizables.hpp>

namespace zoper
{
    void createStandardBackground(
        const mtps::rptr<haf::scene::Renderizables> renderizables);
}

#endif
