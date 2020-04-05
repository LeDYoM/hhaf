#pragma once

#ifndef LIB_ZOPER_APP_EXPORT_INCLUDE_HPP
#define LIB_ZOPER_APP_EXPORT_INCLUDE_HPP

#include <hosted_app/include/iapp.hpp>

extern "C"
{
    haf::IApp *createApp();
    bool destroyApp(haf::IApp *app);
}

#endif
