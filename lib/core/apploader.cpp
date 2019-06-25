#include "apploader.hpp"
#include <loader/include/loader.hpp>

namespace lib::core
{
    AppUniquePtr AppLoader::loadApp(const str& file) const
    {
		using namespace loader;
		auto *loader(createLoader());

        // Temporary. Fake to test.
		static const char *file_name = "zooper_game";
		if (loader->loadModule(file_name))
        {
			auto fp_init_app = (p_initApp)loader->loadMethod(file_name, "createApp");
			auto fp_destroy_app = (p_finishApp)loader->loadMethod(file_name, "destroyApp");

            if (fp_init_app && fp_destroy_app)
            {
                // Both init and destroy functions exist.
                // We can now, load the app.
                auto app = fp_init_app();

                // Create a unique_ptr
                AppUniquePtr app_p{std::move(app)};

                return app_p;
            }
        }
        return {};
    }
}
