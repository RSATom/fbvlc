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

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::RefreshEvent, onRefreshEvent, FB::PluginWindowlessWin)

        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindowWin)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindowWin)
        EVENTTYPE_CASE(FB::ResizedEvent, onWindowResized, FB::PluginWindowWin)
        PLUGIN_EVENT_MAP_CASCADE(FBVLC)
    END_PLUGIN_EVENT_MAP()

private:
    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    bool onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowlessWin *);

    bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowWin *);
    bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowWin *);
    bool onWindowResized(FB::ResizedEvent *evt, FB::PluginWindowWin *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

    void update_window();

public:
    bool is_fullscreen();
    void set_fullscreen(bool fs);
    void toggle_fullscreen();

protected:
    virtual void on_option_change( vlc_player_option_e );
    virtual void on_frame_ready( const std::vector<char>& frame_buf );
    virtual void on_frame_cleanup();

protected:
//for windowless mode
    HBRUSH m_hBgBrush;
//for windowed mode
    std::auto_ptr<WindowedWM> m_wm;
};

#endif//H_FBVLCPLUGIN_WIN
