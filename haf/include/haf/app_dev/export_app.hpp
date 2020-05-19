#ifndef HAF_EXPORT_DEV_INCLUDE_HPP
#define HAF_EXPORT_DEV_INCLUDE_HPP

#ifdef _WIN32
#define APP_EXPORT extern "C" __declspec(dllexport)
#else
#define APP_EXPORT
#endif

#define EXPORT_APP_TYPE(app_type) \
    APP_EXPORT haf::IApp* createApp() \
    { \
        return new app_type(); \
} \
\
APP_EXPORT bool destroyApp(haf::IApp* app) \
{ \
    if (app) \
    { \
        delete app; \
        return true; \
    } \
    return false; \
}

#endif
