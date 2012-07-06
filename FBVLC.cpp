/**********************************************************\

  Auto-generated FBVLC.cpp

  This file contains the auto-generated main plugin object
  implementation for the FireBreathed VLC project

\**********************************************************/

#include "FBVLCAPI.h"

#include "FBVLC.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn FBVLC::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void FBVLC::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
}

///////////////////////////////////////////////////////////////////////////////
/// @fn FBVLC::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void FBVLC::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  FBVLC constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
FBVLC::FBVLC()
    :m_libvlc(0), m_media_width(0), m_media_height(0)
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  FBVLC destructor.
///////////////////////////////////////////////////////////////////////////////
FBVLC::~FBVLC()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

unsigned FBVLC::video_format_cb(char *chroma,
                                unsigned *width, unsigned *height,
                                unsigned *pitches, unsigned *lines)
{
    FB::PluginWindow* w = GetWindow();
    if ( w ) {
        float src_aspect = (float)(*width) / (*height);
        float dst_aspect = (float)w->getWindowWidth()/w->getWindowHeight();
        if ( src_aspect > dst_aspect ) {
            (*width)  = w->getWindowWidth();
            (*height) = static_cast<unsigned>( (*width) / src_aspect );
        }
        else {
            (*height) = w->getWindowHeight();
            (*width)  = static_cast<unsigned>( (*height) * src_aspect );
        }
    }

    m_media_width  = (*width);
    m_media_height = (*height);

    memcpy(chroma, DEF_CHROMA, sizeof(DEF_CHROMA)-1);
    (*pitches) = m_media_width * DEF_PIXEL_BYTES;
    (*lines)   = m_media_height;

    m_frame_buf.resize( m_media_width * m_media_height * DEF_PIXEL_BYTES );

    return 1;
}

void FBVLC::video_cleanup_cb()
{
    m_frame_buf.resize(0);
    m_media_width  = 0;
    m_media_height = 0;
}

void* FBVLC::video_lock_cb(void **planes)
{
    (*planes) = m_frame_buf.empty()? 0 : &m_frame_buf[0];
    return 0;
}

void FBVLC::video_unlock_cb(void* /*picture*/, void *const * /*planes*/)
{
}

void FBVLC::video_display_cb(void * /*picture*/)
{
    FB::PluginWindow* w = GetWindow();
    if ( w ) {
        w->InvalidateWindow();
    }
}

//libvlc events arrives from separate thread
void FBVLC::OnLibVlcEvent_proxy(const libvlc_event_t* e, void *param)
{
    FBVLC* fbvlc = static_cast<FBVLC*>(param);

    FBVLCAPIPtr api  = boost::static_pointer_cast<FBVLCAPI>( fbvlc->getRootJSAPI() );
    FB::BrowserHostPtr h = fbvlc->m_host;

    void (FBVLCAPI::*event_to_fire)(void) = 0;

    switch ( e->type ) {
    //case libvlc_MediaPlayerMediaChanged:
    case libvlc_MediaPlayerNothingSpecial:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerNothingSpecialEvent;
        break;
    case libvlc_MediaPlayerOpening:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerOpeningEvent;
        break;
    case libvlc_MediaPlayerBuffering:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerBufferingEvent;
        break;
    case libvlc_MediaPlayerPlaying:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerPlayingEvent;
        break;
    case libvlc_MediaPlayerPaused:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerPausedEvent;
        break;
    case libvlc_MediaPlayerStopped:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerStoppedEvent;
        break;
    case libvlc_MediaPlayerForward:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerForwardEvent;
        break;
    case libvlc_MediaPlayerBackward:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerBackwardEvent;
        break;
    case libvlc_MediaPlayerEndReached:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerEndReachedEvent;
        break;
    case libvlc_MediaPlayerEncounteredError:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerEncounteredErrorEvent;
        break;
    case libvlc_MediaPlayerTimeChanged:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerTimeChangedEvent;
        break;
    case libvlc_MediaPlayerPositionChanged:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerPositionChangedEvent;
        break;
    case libvlc_MediaPlayerSeekableChanged:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerSeekableChangedEvent;
        break;
    case libvlc_MediaPlayerPausableChanged:
        event_to_fire = &FBVLCAPI::fire_MediaPlayerPausableChangedEvent;
        break;
    //case libvlc_MediaPlayerTitleChanged:
    //    event_to_fire = &FBVLCAPI::fire_MediaPlayerTitleChangedEvent;
    //    break;
    //case libvlc_MediaPlayerSnapshotTaken:
    //    event_to_fire = &FBVLCAPI::fire_MediaPlayerSnapshotTakenEvent;
    //    break;
    //case libvlc_MediaPlayerLengthChanged:
    //    event_to_fire = &FBVLCAPI::fire_MediaPlayerLengthChangedEvent;
    //    break;
    //case libvlc_MediaPlayerVout:
    //    event_to_fire = &FBVLCAPI::fire_MediaPlayerVoutEvent;
    //    break;
    };

    h->ScheduleOnMainThread( api, boost::bind( event_to_fire, api.get() ) );
}

void FBVLC::VlcEvents(bool Attach)
{
    if ( !get_player().is_open() )
        return;

    libvlc_event_manager_t* em =
        libvlc_media_player_event_manager( get_player().get_mp() );
    if(!em)
        return;

    for(int e=libvlc_MediaPlayerMediaChanged; e<=libvlc_MediaPlayerVout; ++e){
        switch(e){
        //case libvlc_MediaPlayerMediaChanged:
        case libvlc_MediaPlayerNothingSpecial:
        case libvlc_MediaPlayerOpening:
        case libvlc_MediaPlayerBuffering:
        case libvlc_MediaPlayerPlaying:
        case libvlc_MediaPlayerPaused:
        case libvlc_MediaPlayerStopped:
        case libvlc_MediaPlayerForward:
        case libvlc_MediaPlayerBackward:
        case libvlc_MediaPlayerEndReached:
        case libvlc_MediaPlayerEncounteredError:
        case libvlc_MediaPlayerTimeChanged:
        case libvlc_MediaPlayerPositionChanged:
        case libvlc_MediaPlayerSeekableChanged:
        case libvlc_MediaPlayerPausableChanged:
        //case libvlc_MediaPlayerTitleChanged:
        //case libvlc_MediaPlayerSnapshotTaken:
        //case libvlc_MediaPlayerLengthChanged:
        //case libvlc_MediaPlayerVout:
            if(Attach)
                libvlc_event_attach(em, e, OnLibVlcEvent_proxy, this);
            else
                libvlc_event_detach(em, e, OnLibVlcEvent_proxy, this);
            break;
        }
    }
}

void FBVLC::open()
{
    if( !m_libvlc ) {
        /* prepare VLC command line */
        const char *libvlc_argv[] = {
            "--no-video-title-show",
    #ifdef _DEBUG
            "-vvv",
    #endif
        };

        m_libvlc = libvlc_new( sizeof(libvlc_argv) / sizeof(libvlc_argv[0]),
                               libvlc_argv );
    }

    if ( m_libvlc && !get_player().is_open() ) {
        get_player().open(m_libvlc);
        VlcEvents(true);
    }

    if ( get_player().is_open() && isWindowless() ) {
        libvlc_video_set_format_callbacks(get_player().get_mp(),
                                          video_format_proxy,
                                          video_cleanup_proxy);

        libvlc_video_set_callbacks(get_player().get_mp(),
                                   video_fb_lock_proxy,
                                   video_fb_unlock_proxy,
                                   video_fb_display_proxy,
                                   this);
    }
}

void FBVLC::close()
{
    get_player().stop();

    if ( get_player().is_open() && isWindowless() ) {

        libvlc_video_set_format_callbacks(get_player().get_mp(),
                                          NULL,
                                          NULL);

        libvlc_video_set_callbacks(get_player().get_mp(),
                                   NULL,
                                   NULL,
                                   NULL,
                                   this);
    }

    if ( get_player().is_open() ) {
        VlcEvents(false);
        get_player().close();
    }

    if ( m_libvlc ) {
        libvlc_free(m_libvlc);
        m_libvlc = 0;
    }
}

void FBVLC::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
    open();
}

void FBVLC::shutdown()
{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<FBVLC> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr FBVLC::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<FBVLCAPI>(FB::ptr_cast<FBVLC>(shared_from_this()), m_host);
}

/*
bool FBVLC::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool FBVLC::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool FBVLC::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}
*/

bool FBVLC::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *)
{
    // The window is attached; act appropriately
    return true;
}

bool FBVLC::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    close();
    return false;
}

void FBVLC::on_player_action( vlc_player_action_e action)
{
    FBVLCAPIPtr api = boost::static_pointer_cast<FBVLCAPI>( getRootJSAPI() );

    switch (action) {
        case pa_play:
            api->fire_PlayEvent();
            break;
        case pa_pause:
            api->fire_PauseEvent();
            break;
        case pa_stop:
            api->fire_StopEvent();
            break;
        //case pa_next:
        //case pa_prev:
        //    break;
    }

}
