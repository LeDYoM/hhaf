#include "app.hpp"
#include "zoperprogramcontroller.hpp"


lib::IApp *createApp()
{
    return new zoper::ZoperProgramController();
}
