#include <loader/include/loader.hpp>
#include <memmanager/include/memmanager.hpp>

// Signature of the main function exported from host shared library
using p_haf_host_main = int (*)(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    int result = 0;
    installMemManager();

    auto* loader(loader::createLoader());

    constexpr const char host_library[] = "host";
    if (loader->loadModule(host_library))
    {
        const auto fp_p_haf_host_main = static_cast<p_haf_host_main>(
            loader->loadMethod(host_library, "haf_host_main"));

        if (fp_p_haf_host_main != nullptr)
        {
            // The haf_host_main method was loaded successfully.
            // Call it.
            result = (*fp_p_haf_host_main)(argc, argv);
        }
        else
        {
            result = -1;
        }
    }
    loader::destroyLoader();
    finishMemManager();
    return result;
}
