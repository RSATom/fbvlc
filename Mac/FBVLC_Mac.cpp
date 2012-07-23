#include "FBVLC_Mac.h"

////////////////////////////////////////////////////////////////////////////////
//FBVLC_Mac class
////////////////////////////////////////////////////////////////////////////////
FBVLC_Mac::FBVLC_Mac()
{
}

FBVLC_Mac::~FBVLC_Mac()
{
}

bool FBVLC_Mac::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowMac *)
{
    vlc_open();
    return true;
}

bool FBVLC_Mac::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowMac *)
{
    vlc_close();
    return true;
}

bool FBVLC_Mac::onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowMac *)
{
    return false;
}
