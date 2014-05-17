/**********************************************************\

  Auto-generated FBVLC.h

  This file contains the auto-generated main plugin object
  implementation for the FireBreathed VLC project

\**********************************************************/
#ifndef H_FBVLCPLUGIN
#define H_FBVLCPLUGIN

#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"
#include "PluginEvents/DrawingEvents.h"

#include "PluginCore.h"

#include <vlc/vlc.h>

#include "libvlc_wrapper/vlc_player.h"
#include "libvlc_wrapper/vlc_vmem.h"
#include "vlc_player_options.h"

FB_FORWARD_PTR(FBVLC)
class FBVLC
    : public FB::PluginCore,
      protected vlc_player,
      protected vlc::vmem,
      protected vlc_player_options
{
public:
    static void StaticInitialize();
    static void StaticDeinitialize();

public:
    FBVLC();
    virtual ~FBVLC();

public:
    void onPluginReady();
    void shutdown();
    virtual FB::JSAPIPtr createJSAPI();
    // If you want your plugin to always be windowless, set this to true
    // If you want your plugin to be optionally windowless based on the
    // value of the "windowless" param tag, remove this method or return
    // FB::PluginCore::isWindowless()
    virtual bool isWindowless() { return FB::PluginCore::isWindowless(); }

    BEGIN_PLUGIN_EVENT_MAP()
        //EVENTTYPE_CASE(FB::MouseDownEvent, onMouseDown, FB::PluginWindow)
        //EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindow)
        //EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        //EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindow)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindow)
        EVENTTYPE_CASE(FB::ResizedEvent, onWindowResized, FB::PluginWindow)
    END_PLUGIN_EVENT_MAP()

private:
    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    //virtual bool onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *);
    //virtual bool onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *);
    //virtual bool onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *);
    bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *);
    bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *);
    bool onWindowResized(FB::ResizedEvent *evt, FB::PluginWindow*);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

public:
    libvlc_instance_t* getLibVlc()
        { return m_libvlc; };
    vlc_player& get_player()
        { return *static_cast<vlc_player*>(this); };
    vlc_player_options& get_options()
        { return *static_cast<vlc_player_options*>(this); }
    const vlc_player_options& get_options() const
        { return *static_cast<const vlc_player_options*>(this); }

    int add_playlist_item( const std::string& mrl );
    int add_playlist_item( const std::string& mrl, const std::vector<std::string>& options );

public:
    virtual bool is_fullscreen() { return false; }
    virtual void set_fullscreen( bool ) {}
    virtual void toggle_fullscreen() {}

private:
    const FB::variant& getParamVariant( const std::string& key ) const;

    void init_vlc_player_options();
    void init_libvlc_options( std::vector<std::string>* );
    void process_startup_options();

    std::string detectHttpProxy( const std::string& mrl ) const;
    bool isTrustedOption( const std::string& option );

protected:
    void vlc_open();
    void vlc_close();

private:
    static void OnLibVlcEvent_proxy(const libvlc_event_t* e, void *param);
    void VlcEvents(bool Attach);

private:
    libvlc_instance_t* m_libvlc;
};
#endif
