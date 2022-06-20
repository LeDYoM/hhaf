#ifndef HAF_BACKEND_BACKEND_EXPORTER_INCLUDE_HPP
#define HAF_BACKEND_BACKEND_EXPORTER_INCLUDE_HPP

#include <backend_client/include/default_functions.hpp>
#include <backend_client/include/default_factory.hpp>
#include <backend_client/include/default_backend_manager.hpp>

#ifdef _WIN32
#define BACKEND_CLIENT_EXPORT extern "C" __declspec(dllexport)
#else
#define BACKEND_CLIENT_EXPORT extern "C" __attribute__((visibility("default")))
#endif

#define DEFINE_DEFAULT_INIT_FUNCTION(b_manager) \
    BACKEND_CLIENT_EXPORT bool init_lib( \
        haf::backend::client::IBackendRegister* const ibackend_register) \
    { \
        return haf::backend::client::default_init_function(&b_manager, \
                                                           ibackend_register); \
    }

#define DEFINE_DEFAULT_FINISH_FUNCTION(b_manager) \
    BACKEND_CLIENT_EXPORT bool finish_lib( \
        haf::backend::client::IBackendRegister* const ibackend_register) \
    { \
        return haf::backend::client::default_finish_function( \
            &b_manager, ibackend_register); \
    }

#define DEFAULT_INIT_FINISH_FUNCTIONS(b_manager)    \
DEFINE_DEFAULT_INIT_FUNCTION(b_manager)   \
DEFINE_DEFAULT_FINISH_FUNCTION(b_manager)

#endif
