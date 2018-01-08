#pragma once

#ifndef ZOPER_COMMON_INCLUDE_HPP__
#define ZOPER_COMMON_INCLUDE_HPP__

#include <lib/core/host.hpp>
#include "zoperprogramcontroller.hpp"

namespace zoper
{
    inline ZoperProgramController &zApp() {
        return app<ZoperProgramController>();
    }
}

#endif