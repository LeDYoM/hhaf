#pragma once

#ifndef LIB_ZOPER_APP_EXPORT_INCLUDE_HPP
#define LIB_ZOPER_APP_EXPORT_INCLUDE_HPP

#include <hosted_app/include/iapp.hpp>

extern "C"
{
    lib::IApp *createApp();
    bool destroyApp(lib::IApp *app);
}

#endif
