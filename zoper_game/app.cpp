#include "app.hpp"
#include "zoperprogramcontroller.hpp"


haf::IApp *createApp()
{
    return new zoper::ZoperProgramController();
}

bool destroyApp(haf::IApp *app)
{
    if (app)
    {
        delete app;
        return true;
    }
    return false;
}
