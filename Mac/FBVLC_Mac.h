#ifndef H_FBVLCPLUGIN_MAC
#define H_FBVLCPLUGIN_MAC

#include "../FBVLC.h"

////////////////////////////////////////////////////////////////////////////////
//FBVLC_Mac class
////////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLC_Mac)
class FBVLC_Mac: public FBVLC
{
public:
    FBVLC_Mac();
    virtual ~FBVLC_Mac();

    //Note: events not routed to FBVLC due to FireBreath limitations
    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowMac)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowMac)
        EVENTTYPE_CASE(FB::RefreshEvent, onRefreshEvent, FB::PluginWindowMac)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowMac *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowMac *);
    virtual bool onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowMac *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/
};

#endif//H_FBVLCPLUGIN_MAC
