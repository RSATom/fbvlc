#ifndef H_FBVLCPLUGIN_WIN
#define H_FBVLCPLUGIN_WIN

#include "../FBVLC.h"
#include "win32_fullscreen.h"

////////////////////////////////////////////////////////////////////////////////
//WindowedWM class
////////////////////////////////////////////////////////////////////////////////
class WindowedWM : public VLCWindowsManager
{
public:
    WindowedWM(HMODULE hDllModule, vlc_player_options* po);

private:
    VLCViewResources m_rc;
};

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

        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowWin)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowWin)
        EVENTTYPE_CASE(FB::ResizedEvent, onWindowResized, FB::PluginWindowWin)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowlessWin *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowlessWin *);
    virtual bool onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowlessWin *);

    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowWin *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowWin *);
    virtual bool onWindowResized(FB::ResizedEvent *evt, FB::PluginWindowWin *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

public:
    bool is_fullscreen();
    void set_fullscreen(bool fs);
    void toggle_fullscreen();

protected:
    virtual void on_option_change(vlc_player_option_e );
//for windowless mode
    HBRUSH m_hBgBrush;
//for windowed mode
    std::auto_ptr<WindowedWM> m_wm;
};

#endif//H_FBVLCPLUGIN_WIN
