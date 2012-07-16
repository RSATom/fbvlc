#ifndef H_FBVLCPLUGIN_WIN
#define H_FBVLCPLUGIN_WIN

#include "../FBVLC.h"

////////////////////////////////////////////////////////////////////////////////
//FBVLC_Win class
////////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLC_Win)
class FBVLC_Win: public FBVLC
{
public:
    FBVLC_Win();
    virtual ~FBVLC_Win();

    //Note: events not routed to FBVLC due to FireBreath limitations
    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::RefreshEvent, onRefreshEvent, FB::PluginWindowlessWin)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowlessWin)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowlessWin)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowlessWin *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowlessWin *);
    virtual bool onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowlessWin *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

protected:
    virtual void on_option_change(vlc_player_option_e );
    HBRUSH m_hBgBrush;
};

#endif//H_FBVLCPLUGIN_WIN
