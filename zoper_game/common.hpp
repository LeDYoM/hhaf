#pragma once

#ifndef ZOPER_COMMON_INCLUDE_HPP
#define ZOPER_COMMON_INCLUDE_HPP

#include <lib/core/host.hpp>
#include "zoperprogramcontroller.hpp"

namespace zoper
{
    
    inline ZoperProgramController &zApp() {
        return app<ZoperProgramController>();
    }
    
}

#endif