#include <backend_client/include/default_backend_manager.hpp>

class HafIntegratedBackendManager : public haf::backend::client::DefaultBackendManager
{
public:
    void create() override;
};
