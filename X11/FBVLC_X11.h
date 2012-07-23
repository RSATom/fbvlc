#ifndef H_FBVLCPLUGIN_X11
#define H_FBVLCPLUGIN_X11

#include "../FBVLC.h"

////////////////////////////////////////////////////////////////////////////////
//FBVLC_X11 class
////////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLC_X11)
class FBVLC_X11: public FBVLC
{
public:
    FBVLC_X11();
    virtual ~FBVLC_X11();

    //Note: events not routed to FBVLC due to FireBreath limitations
    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowX11)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowX11)
        EVENTTYPE_CASE(FB::RefreshEvent, onRefreshEvent, FB::PluginWindow)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowX11 *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowX11 *);
    virtual bool onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowX11 *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/
};

#endif//H_FBVLCPLUGIN_X11
