#include "FBVLC_X11.h"

////////////////////////////////////////////////////////////////////////////////
//FBVLC_X11 class
////////////////////////////////////////////////////////////////////////////////
FBVLC_X11::FBVLC_X11()
{
}

FBVLC_X11::~FBVLC_X11()
{
}

bool FBVLC_X11::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowX11 *)
{
    vlc_open();
    return true;
}

bool FBVLC_X11::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowX11 *)
{
    vlc_close();
    return true;
}

bool FBVLC_X11::onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowX11 *)
{
    return false;
}
