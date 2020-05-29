#include <loader/include/loader.hpp>

using p_haf_host_main   = int (*)(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    auto* loader(loader::createLoader());

    constexpr const char host_library[] = "host";
    if (loader->loadModule(host_library))
    {
        const auto fp_p_haf_host_main = static_cast<p_haf_host_main>(
            loader->loadMethod(host_library, "haf_host_main"));

        if (fp_p_haf_host_main != nullptr)
        {
            return (*fp_p_haf_host_main)(argc, argv);
        }

        return -1;
    }
    return -2;
}
