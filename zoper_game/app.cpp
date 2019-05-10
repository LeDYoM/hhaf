#include "app.hpp"
#include "zoperprogramcontroller.hpp"


lib::IApp *createApp()
{
    return new zoper::ZoperProgramController();
}

bool destroyApp(lib::IApp *app)
{
    if (app)
    {
        delete app;
        return true;
    }
    return false;
}
