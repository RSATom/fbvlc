#ifndef H_FBVLCPLUGIN_X11
#define H_FBVLCPLUGIN_X11

#include "../FBVLC.h"

#include "X11/PluginWindowX11.h"

#include "X11WindowlessWindow.h"
#include "X11ExposeEvent.h"

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
        EVENTTYPE_CASE( FB::AttachedEvent, onWindowAttached, FB::PluginWindowX11 )
        EVENTTYPE_CASE( FB::DetachedEvent, onWindowDetached, FB::PluginWindowX11 )

        EVENTTYPE_CASE( FB::AttachedEvent, onWindowAttached, X11WindowlessWindow )
        EVENTTYPE_CASE( FB::DetachedEvent, onWindowDetached, X11WindowlessWindow )
        EVENTTYPE_CASE( X11ExposeEvent, onExposeEvent, X11WindowlessWindow )
        PLUGIN_EVENT_MAP_CASCADE( FBVLC )
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    bool onWindowAttached( FB::AttachedEvent*, FB::PluginWindowX11* );
    bool onWindowDetached( FB::DetachedEvent*, FB::PluginWindowX11* );

    bool onWindowAttached( FB::AttachedEvent*, X11WindowlessWindow* );
    bool onWindowDetached( FB::DetachedEvent*, X11WindowlessWindow* );
    bool onExposeEvent( X11ExposeEvent*, X11WindowlessWindow* );
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

protected:
    virtual void on_option_change( vlc_player_option_e );

protected:
   virtual void on_frame_ready( const std::vector<char>& ) { updateWindow(); }
   virtual void on_frame_cleanup() { updateWindow(); }

private:
    void updateWindow();
    void updateBgColor();
    void fillBackground( xcb_drawable_t drawable,
                         const xcb_rectangle_t* bgRects,
                         uint32_t rectCount );

private:
    xcb_connection_t* m_xcbConnection;
    xcb_gcontext_t m_xcbContextId;
};

#endif//H_FBVLCPLUGIN_X11
