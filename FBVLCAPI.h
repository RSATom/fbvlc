/**********************************************************\

  Auto-generated FBVLCAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "FBVLC.h"

#ifndef H_FBVLCAPI
#define H_FBVLCAPI

////////////////////////////////////////////////////////////////////////////
/// FBVLCAudioAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLCAudioAPI)
class FBVLCAudioAPI : public FB::JSAPIAuto
{
public:
    FBVLCAudioAPI(const FBVLCPtr& plugin, const FB::BrowserHostPtr& host)
      :m_plugin(plugin), m_host(host)
    {
    }

    virtual ~FBVLCAudioAPI() {};

    FBVLCPtr getPlugin();

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCInputAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLCInputAPI)
class FBVLCInputAPI : public FB::JSAPIAuto
{
public:
    FBVLCInputAPI(const FBVLCPtr& plugin, const FB::BrowserHostPtr& host)
        :m_plugin(plugin), m_host(host)
    {
    }

    virtual ~FBVLCInputAPI(){}

    FBVLCPtr getPlugin();

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCPlaylistAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLCPlaylistAPI)
class FBVLCPlaylistAPI : public FB::JSAPIAuto
{
public:
    FBVLCPlaylistAPI(const FBVLCPtr& plugin, const FB::BrowserHostPtr& host)
        :m_plugin(plugin), m_host(host)
    {
    }

    virtual ~FBVLCPlaylistAPI(){}

    FBVLCPtr getPlugin();

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCSubtitleAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLCSubtitleAPI)
class FBVLCSubtitleAPI : public FB::JSAPIAuto
{
public:
    FBVLCSubtitleAPI(const FBVLCPtr& plugin, const FB::BrowserHostPtr& host)
        :m_plugin(plugin), m_host(host)
    {
    }

    virtual ~FBVLCSubtitleAPI(){}

    FBVLCPtr getPlugin();

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCVideoAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLCVideoAPI)
class FBVLCVideoAPI : public FB::JSAPIAuto
{
public:
    FBVLCVideoAPI(const FBVLCPtr& plugin, const FB::BrowserHostPtr& host)
        :m_plugin(plugin), m_host(host)
    {
    }

    virtual ~FBVLCVideoAPI(){}

    FBVLCPtr getPlugin();

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCMediaDescAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLCMediaDescAPI)
class FBVLCMediaDescAPI : public FB::JSAPIAuto
{
public:
    FBVLCMediaDescAPI(const FBVLCPtr& plugin, const FB::BrowserHostPtr& host)
        :m_plugin(plugin), m_host(host)
    {
    }

    virtual ~FBVLCMediaDescAPI(){}

    FBVLCPtr getPlugin();

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLCAPI)
class FBVLCAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn FBVLCAPI::FBVLCAPI(const FBVLCPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    FBVLCAPI(const FBVLCPtr& plugin, const FB::BrowserHostPtr& host)
      :m_plugin(plugin), m_host(host)
    {
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &FBVLCAPI::get_version));

        registerMethod("play",            make_method(this, &FBVLCAPI::play));
        registerMethod("togglePause",     make_method(this, &FBVLCAPI::togglePause));
        registerMethod("stop",            make_method(this, &FBVLCAPI::stop));
        registerMethod("toggleMute",      make_method(this, &FBVLCAPI::toggleMute));

        registerProperty("bgcolor",       make_property(this, &FBVLCAPI::get_bgcolor,
                                                              &FBVLCAPI::set_bgcolor));

        registerAttribute("libvlc_NothingSpecial", libvlc_NothingSpecial, true);
        registerAttribute("libvlc_Opening",        libvlc_Opening,        true);
        registerAttribute("libvlc_Buffering",      libvlc_Buffering,      true);
        registerAttribute("libvlc_Playing",        libvlc_Playing,        true);
        registerAttribute("libvlc_Paused",         libvlc_Paused,         true);
        registerAttribute("libvlc_Stopped",        libvlc_Stopped,        true);
        registerAttribute("libvlc_Ended",          libvlc_Ended,          true);
        registerAttribute("libvlc_Error",          libvlc_Error,          true);
        registerProperty("state",    make_property(this, &FBVLCAPI::get_state));

        m_audio = boost::make_shared<FBVLCAudioAPI>(plugin, m_host);
        registerProperty("audio", make_property(this, &FBVLCAPI::get_audio));

        m_input = boost::make_shared<FBVLCInputAPI>(plugin, m_host);
        registerProperty("input", make_property(this, &FBVLCAPI::get_input));

        m_playlist = boost::make_shared<FBVLCPlaylistAPI>(plugin, m_host);
        registerProperty("playlist", make_property(this, &FBVLCAPI::get_playlist));

        m_subtitle = boost::make_shared<FBVLCSubtitleAPI>(plugin, m_host);
        registerProperty("subtitle", make_property(this, &FBVLCAPI::get_subtitle));

        m_video = boost::make_shared<FBVLCVideoAPI>(plugin, m_host);
        registerProperty("video", make_property(this, &FBVLCAPI::get_video));

        m_mediaDesc = boost::make_shared<FBVLCMediaDescAPI>(plugin, m_host);
        registerProperty("mediaDesc", make_property(this, &FBVLCAPI::get_mediaDesc));

    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn FBVLCAPI::~FBVLCAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~FBVLCAPI() {};

    FBVLCPtr getPlugin();

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    void play(const std::string& mrl);
    void togglePause();
    void stop();

    void toggleMute();

    std::string get_bgcolor();
    void set_bgcolor(const std::string& bg);

    int FBVLCAPI::get_state();

    FBVLCAudioAPIWeakPtr     get_audio()     { return m_audio; }
    FBVLCInputAPIWeakPtr     get_input()     { return m_input; }
    FBVLCPlaylistAPIWeakPtr  get_playlist()  { return m_playlist; }
    FBVLCSubtitleAPIWeakPtr  get_subtitle()  { return m_subtitle; }
    FBVLCVideoAPIWeakPtr     get_video()     { return m_video; }
    FBVLCMediaDescAPIWeakPtr get_mediaDesc() { return m_mediaDesc; }

    //events
    FB_JSAPI_EVENT(PlayEvent, 0, ());
    FB_JSAPI_EVENT(PauseEvent, 0, ());
    FB_JSAPI_EVENT(StopEvent, 0, ());

    /* async events from libvlc */
    FB_JSAPI_EVENT(MediaPlayerNothingSpecial, 0, ());
    FB_JSAPI_EVENT(MediaPlayerOpening, 0, ());
    FB_JSAPI_EVENT(MediaPlayerBuffering, 0, ());
    FB_JSAPI_EVENT(MediaPlayerPlaying, 0, ());
    FB_JSAPI_EVENT(MediaPlayerPaused, 0, ());
    FB_JSAPI_EVENT(MediaPlayerForward, 0, ());
    FB_JSAPI_EVENT(MediaPlayerBackward, 0, ());
    FB_JSAPI_EVENT(MediaPlayerEncounteredError, 0, ());
    FB_JSAPI_EVENT(MediaPlayerEndReached, 0, ());
    FB_JSAPI_EVENT(MediaPlayerStopped, 0, ());

    FB_JSAPI_EVENT(MediaPlayerTimeChanged, 0, ());
    FB_JSAPI_EVENT(MediaPlayerPositionChanged, 0, ());
    FB_JSAPI_EVENT(MediaPlayerSeekableChanged, 0, ());
    FB_JSAPI_EVENT(MediaPlayerPausableChanged, 0, ());

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    FBVLCAudioAPIPtr     m_audio;
    FBVLCInputAPIPtr     m_input;
    FBVLCPlaylistAPIPtr  m_playlist;
    FBVLCSubtitleAPIPtr  m_subtitle;
    FBVLCVideoAPIPtr     m_video;
    FBVLCMediaDescAPIPtr m_mediaDesc;
};

#endif // H_FBVLCAPI
