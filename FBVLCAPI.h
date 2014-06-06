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
FB_FORWARD_PTR( FBVLCAudioAPI )
class FBVLCAudioAPI : public FB::JSAPIAuto
{
public:
    FBVLCAudioAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        : m_plugin( plugin ), m_host( host )
    {
        registerProperty( "count",
                          make_property( this,
                                         &FBVLCAudioAPI::get_trackCount ) );
        registerProperty( "trackCount",
                          make_property( this,
                                         &FBVLCAudioAPI::get_trackCount ) );
        registerProperty( "track",
                          make_property( this, &FBVLCAudioAPI::get_track,
                                               &FBVLCAudioAPI::set_track ) );
        registerProperty( "mute",
                          make_property( this, &FBVLCAudioAPI::get_mute,
                                               &FBVLCAudioAPI::set_mute ) );
        registerProperty( "volume",
                          make_property( this, &FBVLCAudioAPI::get_volume,
                                               &FBVLCAudioAPI::set_volume ) );

        registerAttribute( "libvlc_AudioChannel_Error",   libvlc_AudioChannel_Error,   true );
        registerAttribute( "libvlc_AudioChannel_Stereo",  libvlc_AudioChannel_Stereo,  true );
        registerAttribute( "libvlc_AudioChannel_RStereo", libvlc_AudioChannel_RStereo, true );
        registerAttribute( "libvlc_AudioChannel_Left",    libvlc_AudioChannel_Left,    true );
        registerAttribute( "libvlc_AudioChannel_Right",   libvlc_AudioChannel_Right,   true );
        registerAttribute( "libvlc_AudioChannel_Dolbys",  libvlc_AudioChannel_Dolbys,  true );

        registerAttribute( "Error",                       libvlc_AudioChannel_Error,   true );
        registerAttribute( "stereo",                      libvlc_AudioChannel_Stereo,  true );
        registerAttribute( "reverseStereoeo",             libvlc_AudioChannel_RStereo, true );
        registerAttribute( "left",                        libvlc_AudioChannel_Left,    true );
        registerAttribute( "right",                       libvlc_AudioChannel_Right,   true );
        registerAttribute( "dolby",                       libvlc_AudioChannel_Dolbys,  true );

        registerProperty( "channel",
                          make_property( this, &FBVLCAudioAPI::get_channel,
                                               &FBVLCAudioAPI::set_channel ) );

        registerMethod( "toggleMute",
                        make_method( this, &FBVLCAudioAPI::toggleMute ) );
        registerMethod( "description",
                        make_method( this, &FBVLCAudioAPI::description ) );
    }

    virtual ~FBVLCAudioAPI(){};

    FBVLCPtr getPlugin();

    unsigned get_trackCount();

    bool get_mute();
    void set_mute( bool );

    unsigned int get_volume();
    void set_volume( unsigned int );

    int get_track();
    void set_track( int idx );

    unsigned int get_channel();
    void set_channel( unsigned int );

    void toggleMute();

    std::string description( unsigned int trackID );

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCInputAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCInputAPI )
class FBVLCInputAPI : public FB::JSAPIAuto
{
public:
    FBVLCInputAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        :m_plugin( plugin ), m_host( host )
    {
        registerProperty( "length",
                          make_property( this, &FBVLCInputAPI::get_length ) );
        registerProperty( "fps",
                          make_property( this, &FBVLCInputAPI::get_fps ) );
        registerProperty( "hasVout",
                          make_property( this, &FBVLCInputAPI::get_hasVout ) );
        registerProperty( "state",
                          make_property( this, &FBVLCInputAPI::get_state ) );

        registerProperty( "position",
                          make_property( this, &FBVLCInputAPI::get_position,
                                               &FBVLCInputAPI::set_position ) );
        registerProperty( "time",
                          make_property(this, &FBVLCInputAPI::get_time,
                                              &FBVLCInputAPI::set_time ) );
        registerProperty( "rate",
                          make_property( this, &FBVLCInputAPI::get_rate,
                                               &FBVLCInputAPI::set_rate ) );
    }

    virtual ~FBVLCInputAPI(){}

    FBVLCPtr getPlugin();

    double get_length();
    double get_fps();
    bool get_hasVout();
    unsigned int get_state();

    double get_position();
    void set_position( double );

    double get_time();
    void set_time( double );

    double get_rate();
    void set_rate( double );

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCPlaylistItemsAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCPlaylistItemsAPI )
class FBVLCPlaylistItemsAPI : public FB::JSAPIAuto
{
public:
    FBVLCPlaylistItemsAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        : m_plugin( plugin ), m_host( host )
    {
        registerProperty( "count",
                          make_property( this, &FBVLCPlaylistItemsAPI::get_count ) );

        registerMethod( "clear",
                        make_method( this, &FBVLCPlaylistItemsAPI::clear ) );
        registerMethod( "remove",
                        make_method( this, &FBVLCPlaylistItemsAPI::remove ) );
    }

    virtual ~FBVLCPlaylistItemsAPI(){}

    FBVLCPtr getPlugin();

    unsigned int get_count();
    void clear();
    bool remove( unsigned int idx );

    virtual FB::variant GetProperty( int idx );

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCPlaylistAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCPlaylistAPI )
class FBVLCPlaylistAPI : public FB::JSAPIAuto
{
public:
    FBVLCPlaylistAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        : m_plugin( plugin ), m_host( host )
    {
        registerProperty( "itemCount",
                          make_property( this, &FBVLCPlaylistAPI::get_itemCount ) );
        registerProperty( "isPlaying",
                          make_property( this, &FBVLCPlaylistAPI::get_isPlaying ) );
        registerProperty( "currentItem",
                          make_property( this, &FBVLCPlaylistAPI::get_current ) );

        registerMethod( "add",
                        make_method( this, &FBVLCPlaylistAPI::add ) );
        registerMethod( "addWithOptions",
                        make_method( this, &FBVLCPlaylistAPI::addWithOptions ) );
        registerMethod( "play",
                        make_method( this, &FBVLCPlaylistAPI::play ) );
        registerMethod( "playItem",
                        make_method( this, &FBVLCPlaylistAPI::playItem ) );
        registerMethod( "setCurrentItem",
                        make_method( this, &FBVLCPlaylistAPI::setCurrentItem ) );
        registerMethod( "pause",
                        make_method( this, &FBVLCPlaylistAPI::pause ) );
        registerMethod( "togglePause",
                        make_method( this, &FBVLCPlaylistAPI::togglePause ) );
        registerMethod( "stop",
                        make_method( this, &FBVLCPlaylistAPI::stop ) );
        registerMethod( "next",
                        make_method( this, &FBVLCPlaylistAPI::next ) );
        registerMethod( "prev",
                        make_method( this, &FBVLCPlaylistAPI::prev ) );
        registerMethod( "clear",
                        make_method( this, &FBVLCPlaylistAPI::clear ) );
        registerMethod( "removeItem",
                        make_method( this, &FBVLCPlaylistAPI::removeItem ) );

        m_items = boost::make_shared<FBVLCPlaylistItemsAPI>( plugin, m_host );
        registerProperty( "items", make_property( this, &FBVLCPlaylistAPI::get_items ) );
    }

    virtual ~FBVLCPlaylistAPI(){}

    FBVLCPtr getPlugin();

    unsigned int get_itemCount();
    bool get_isPlaying();
    int get_current();

    int add( const std::string& mrl );
    int addWithOptions( const std::string& mrl,
                        const std::vector<std::string>& options );

    void play();
    bool playItem( unsigned int idx );
    void setCurrentItem( unsigned int idx );
    void pause();
    void togglePause();
    void stop();
    void next();
    void prev();
    void clear();
    bool removeItem( unsigned int idx );

    FBVLCPlaylistItemsAPIPtr get_items() { return m_items; }

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    FBVLCPlaylistItemsAPIPtr m_items;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCSubtitleAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCSubtitleAPI )
class FBVLCSubtitleAPI : public FB::JSAPIAuto
{
public:
    FBVLCSubtitleAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        : m_plugin( plugin ), m_host( host )
    {
        registerProperty( "count",
                          make_property( this, &FBVLCSubtitleAPI::get_trackCount ) );
        registerProperty( "trackCount",
                          make_property( this, &FBVLCSubtitleAPI::get_trackCount ) );

        registerProperty( "track",
                          make_property( this, &FBVLCSubtitleAPI::get_track,
                                               &FBVLCSubtitleAPI::set_track ) );

        registerMethod( "description",
                        make_method( this, &FBVLCSubtitleAPI::description ) );
    }

    virtual ~FBVLCSubtitleAPI(){}

    FBVLCPtr getPlugin();

    unsigned get_trackCount();

    int get_track();
    void set_track( int idx );

    std::string description( unsigned int i );

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCMarqueeAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCMarqueeAPI )
class FBVLCMarqueeAPI : public FB::JSAPIAuto
{
public:
    FBVLCMarqueeAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        :m_plugin( plugin ), m_host( host )
    {
        registerProperty( "text",
                          make_property( this, &FBVLCMarqueeAPI::get_text,
                                               &FBVLCMarqueeAPI::set_text ) );
        registerProperty( "color",
                          make_property( this, &FBVLCMarqueeAPI::get_color,
                                               &FBVLCMarqueeAPI::set_color ) );
        registerProperty( "opacity",
                          make_property( this, &FBVLCMarqueeAPI::get_opacity,
                                               &FBVLCMarqueeAPI::set_opacity ) );
        registerProperty( "position",
                          make_property( this, &FBVLCMarqueeAPI::get_position,
                                               &FBVLCMarqueeAPI::set_position ) );
        registerProperty( "refresh",
                          make_property( this, &FBVLCMarqueeAPI::get_refresh,
                                              &FBVLCMarqueeAPI::set_refresh ) );
        registerProperty( "size",
                          make_property( this, &FBVLCMarqueeAPI::get_size,
                                               &FBVLCMarqueeAPI::set_size ) );
        registerProperty( "timeout",
                          make_property( this, &FBVLCMarqueeAPI::get_timeout,
                                               &FBVLCMarqueeAPI::set_timeout ) );
        registerProperty( "x",
                          make_property( this, &FBVLCMarqueeAPI::get_x,
                                               &FBVLCMarqueeAPI::set_x ) );
        registerProperty( "y",
                          make_property( this, &FBVLCMarqueeAPI::get_y,
                                             &FBVLCMarqueeAPI::set_y ) );

        registerMethod( "enable",
                        make_method( this, &FBVLCMarqueeAPI::enable ) );
        registerMethod( "disable",
                        make_method( this, &FBVLCMarqueeAPI::disable ) );
    }

    virtual ~FBVLCMarqueeAPI(){}

    FBVLCPtr getPlugin();

    std::string get_text();
    void set_text( const std::string& t );

    std::string get_position();
    void set_position( const std::string& p );

    unsigned int get_color()
        { return get_marquee_int( libvlc_marquee_Color ); };
    void set_color(unsigned int c)
        { set_marquee_int( libvlc_marquee_Color, c ); };

    unsigned int get_opacity()
        { return get_marquee_int( libvlc_marquee_Opacity ); };
    void set_opacity( unsigned int o )
        { set_marquee_int( libvlc_marquee_Opacity, o ); };

    unsigned int get_refresh()
        { return get_marquee_int( libvlc_marquee_Refresh ); };
    void set_refresh( unsigned int r )
        { set_marquee_int( libvlc_marquee_Refresh, r ); };

    unsigned int get_size()
        { return get_marquee_int( libvlc_marquee_Size ); };
    void set_size( unsigned int s )
        { set_marquee_int( libvlc_marquee_Size, s ); };

    unsigned int get_timeout()
        { return get_marquee_int( libvlc_marquee_Timeout ); };
    void set_timeout( unsigned int t )
        { set_marquee_int( libvlc_marquee_Timeout, t ); };

    unsigned int get_x()
        { return get_marquee_int( libvlc_marquee_X ); };
    void set_x( unsigned int x )
        { set_marquee_int( libvlc_marquee_X, x ); };

    unsigned int get_y()
        { return get_marquee_int( libvlc_marquee_Y ); };
    void set_y( unsigned int y )
        { set_marquee_int( libvlc_marquee_Y, y ); };

    void enable()
        { set_marquee_int( libvlc_marquee_Enable, 1 ); };
    void disable()
        { set_marquee_int( libvlc_marquee_Enable, 0 ); };

private:
    int get_marquee_int( libvlc_video_marquee_option_t );
    void set_marquee_int( libvlc_video_marquee_option_t, int i );

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCLogoAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCLogoAPI )
class FBVLCLogoAPI : public FB::JSAPIAuto
{
public:
    FBVLCLogoAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        : m_plugin( plugin ), m_host( host )
    {
        registerProperty( "position",
                          make_property( this, &FBVLCLogoAPI::get_position,
                                             &FBVLCLogoAPI::set_position ) );
        registerProperty( "opacity",
                          make_property( this, &FBVLCLogoAPI::get_opacity,
                                               &FBVLCLogoAPI::set_opacity ) );
        registerProperty( "delay",
                          make_property( this, &FBVLCLogoAPI::get_delay,
                                               &FBVLCLogoAPI::set_delay ) );
        registerProperty( "repeat",
                          make_property( this, &FBVLCLogoAPI::get_repeat,
                                               &FBVLCLogoAPI::set_repeat ) );
        registerProperty( "x",
                          make_property( this, &FBVLCLogoAPI::get_x,
                                               &FBVLCLogoAPI::set_x ) );
        registerProperty( "y",
                          make_property( this, &FBVLCLogoAPI::get_y,
                                               &FBVLCLogoAPI::set_y ) );

        registerMethod( "enable",
                        make_method( this, &FBVLCLogoAPI::enable ) );
        registerMethod( "disable",
                        make_method( this, &FBVLCLogoAPI::disable ) );
        registerMethod( "file",
                        make_method( this, &FBVLCLogoAPI::file ) );
    }

    virtual ~FBVLCLogoAPI(){}

    FBVLCPtr getPlugin();

    std::string get_position();
    void set_position( const std::string& );

    unsigned int get_opacity()
        { return get_logo_int( libvlc_logo_opacity ); };
    void set_opacity( unsigned int o )
        { set_logo_int( libvlc_logo_opacity, o ); };

    unsigned int get_delay()
        { return get_logo_int( libvlc_logo_delay ); };
    void set_delay( unsigned int d )
        { set_logo_int( libvlc_logo_delay, d ); };

    int get_repeat()
        { return get_logo_int( libvlc_logo_repeat ); };
    void set_repeat( int r )
        { set_logo_int( libvlc_logo_repeat, r ); };

    unsigned int get_x()
        { return get_logo_int( libvlc_logo_x ); };
    void set_x( unsigned int x )
        { set_logo_int( libvlc_logo_x, x ); };

    unsigned int get_y()
        { return get_logo_int( libvlc_logo_y ); };
    void set_y( unsigned int y )
        { set_logo_int( libvlc_logo_y, y ); };

    void enable()
        { return set_logo_int( libvlc_logo_enable, 1 ); }
    void disable()
        { return set_logo_int( libvlc_logo_enable, 0 ); }

    void file( const std::string& );

private:
    int get_logo_int( libvlc_video_logo_option_t );
    void set_logo_int( libvlc_video_logo_option_t, int i );

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCDeinterlaceAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCDeinterlaceAPI )
class FBVLCDeinterlaceAPI : public FB::JSAPIAuto
{
public:
    FBVLCDeinterlaceAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        : m_plugin( plugin ), m_host( host )
    {
        registerMethod( "enable",
                       make_method( this, &FBVLCDeinterlaceAPI::enable ) );
        registerMethod( "disable",
                       make_method( this, &FBVLCDeinterlaceAPI::disable ) );
    }

    virtual ~FBVLCDeinterlaceAPI(){}

    FBVLCPtr getPlugin();

    void enable( const std::string& mode );
    void disable();

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCVideoAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCVideoAPI )
class FBVLCVideoAPI : public FB::JSAPIAuto
{
public:
    FBVLCVideoAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host )
        : m_plugin( plugin ), m_host( host )
    {
        registerProperty( "width",
                          make_property( this, &FBVLCVideoAPI::get_width ) );
        registerProperty( "height",
                          make_property( this, &FBVLCVideoAPI::get_height ) );
        registerProperty( "trackCount",
                          make_property( this, &FBVLCVideoAPI::get_trackCount ) );
        registerProperty( "track",
                          make_property( this, &FBVLCVideoAPI::get_track,
                                               &FBVLCVideoAPI::set_track ) );

        registerProperty( "aspectRatio",
                          make_property( this, &FBVLCVideoAPI::get_aspectRatio,
                                               &FBVLCVideoAPI::set_aspectRatio ) );
        registerProperty( "subtitle",
                          make_property( this, &FBVLCVideoAPI::get_subtitle,
                                               &FBVLCVideoAPI::set_subtitle ) );
        registerProperty( "crop",
                          make_property( this, &FBVLCVideoAPI::get_crop,
                                               &FBVLCVideoAPI::set_crop ) );
        registerProperty( "teletext",
                          make_property( this, &FBVLCVideoAPI::get_teletext,
                                               &FBVLCVideoAPI::set_teletext ) );
        registerProperty( "fullscreen",
                          make_property( this, &FBVLCVideoAPI::get_fullscreen,
                                               &FBVLCVideoAPI::set_fullscreen ) );

        registerProperty( "contrast",
                          make_property( this, &FBVLCVideoAPI::get_contrast,
                                               &FBVLCVideoAPI::set_contrast ) );
        registerProperty( "brightness",
                          make_property( this, &FBVLCVideoAPI::get_brightness,
                                               &FBVLCVideoAPI::set_brightness ) );
        registerProperty( "hue",
                          make_property( this, &FBVLCVideoAPI::get_hue,
                                               &FBVLCVideoAPI::set_hue ) );
        registerProperty( "saturation",
                          make_property( this, &FBVLCVideoAPI::get_saturation,
                                               &FBVLCVideoAPI::set_saturation ) );
        registerProperty( "gamma",
                          make_property( this, &FBVLCVideoAPI::get_gamma,
                                               &FBVLCVideoAPI::set_gamma ) );

        registerMethod( "toggleTeletext",
                        make_method( this, &FBVLCVideoAPI::toggleTeletext ) );
        registerMethod( "toggleFullscreen",
                        make_method( this, &FBVLCVideoAPI::toggleFullscreen ) );

        m_marquee = boost::make_shared<FBVLCMarqueeAPI>( plugin, m_host );
        registerProperty( "marquee", make_property( this, &FBVLCVideoAPI::get_marquee ) );

        m_logo = boost::make_shared<FBVLCLogoAPI>( plugin, m_host );
        registerProperty( "logo", make_property( this, &FBVLCVideoAPI::get_logo ) );

        m_deinterlace = boost::make_shared<FBVLCDeinterlaceAPI>( plugin, m_host );
        registerProperty( "deinterlace", make_property( this, &FBVLCVideoAPI::get_deinterlace ) );
    }

    virtual ~FBVLCVideoAPI(){}

    FBVLCPtr getPlugin();

    unsigned int get_width();
    unsigned int get_height();

    unsigned get_trackCount();

    int get_track();
    void set_track( int idx );

    bool get_fullscreen();
    void set_fullscreen( bool fs );

    void toggleFullscreen();

    std::string get_aspectRatio();
    void set_aspectRatio( const std::string& );

    int get_subtitle();
    void set_subtitle( unsigned int );

    std::string get_crop();
    void set_crop( const std::string& );

    int get_teletext();
    void set_teletext( unsigned int );

    void toggleTeletext();

    float get_contrast();
    void set_contrast( float v );

    float get_brightness();
    void set_brightness( float v );

    float get_hue();
    void set_hue( float v );

    float get_saturation();
    void set_saturation( float v );

    float get_gamma();
    void set_gamma( float v );

    FBVLCMarqueeAPIWeakPtr     get_marquee()     { return m_marquee; };
    FBVLCLogoAPIWeakPtr        get_logo()        { return m_logo; }
    FBVLCDeinterlaceAPIWeakPtr get_deinterlace() { return m_deinterlace; }

private:
    void getVideoSize( unsigned* width, unsigned* height );

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    FBVLCMarqueeAPIPtr     m_marquee;
    FBVLCLogoAPIPtr        m_logo;
    FBVLCDeinterlaceAPIPtr m_deinterlace;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCMediaDescAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCMediaDescAPI )
class FBVLCMediaDescAPI : public FB::JSAPIAuto
{
public:
    FBVLCMediaDescAPI( const FBVLCPtr& plugin )
        : m_plugin( plugin )
    {
        registerProperty( "title",
                          make_property( this, &FBVLCMediaDescAPI::get_title ) );
        registerProperty( "artist",
                          make_property( this, &FBVLCMediaDescAPI::get_artist ) );
        registerProperty( "genre",
                          make_property( this, &FBVLCMediaDescAPI::get_genre ) );
        registerProperty( "copyright",
                          make_property( this, &FBVLCMediaDescAPI::get_copyright ) );
        registerProperty( "album",
                          make_property( this, &FBVLCMediaDescAPI::get_album ) );
        registerProperty( "trackNumber",
                          make_property( this, &FBVLCMediaDescAPI::get_trackNumber ) );
        registerProperty( "description",
                          make_property( this, &FBVLCMediaDescAPI::get_description ) );
        registerProperty( "rating",
                          make_property( this, &FBVLCMediaDescAPI::get_rating ) );
        registerProperty( "date",
                          make_property( this, &FBVLCMediaDescAPI::get_date ) );
        registerProperty( "setting",
                          make_property( this, &FBVLCMediaDescAPI::get_setting ) );
        registerProperty( "URL",
                          make_property( this, &FBVLCMediaDescAPI::get_URL ) );
        registerProperty( "language",
                          make_property( this, &FBVLCMediaDescAPI::get_language ) );
        registerProperty( "nowPlaying",
                          make_property( this, &FBVLCMediaDescAPI::get_nowPlaying ) );
        registerProperty( "publisher",
                          make_property( this, &FBVLCMediaDescAPI::get_publisher ) );
        registerProperty( "encodedBy",
                          make_property( this, &FBVLCMediaDescAPI::get_encodedBy ) );
        registerProperty( "artworkURL",
                          make_property( this, &FBVLCMediaDescAPI::get_artworkURL ) );
        registerProperty( "trackID",
                          make_property( this, &FBVLCMediaDescAPI::get_trackID ) );
        registerProperty( "mrl",
                          make_property( this, &FBVLCMediaDescAPI::get_mrl ) );
    }

    virtual ~FBVLCMediaDescAPI(){}

    FBVLCPtr getPlugin();

    std::string get_title();
    std::string get_artist();
    std::string get_genre();
    std::string get_copyright();
    std::string get_album();
    std::string get_trackNumber();
    std::string get_description();
    std::string get_rating();
    std::string get_date();
    std::string get_setting();
    std::string get_URL();
    std::string get_language();
    std::string get_nowPlaying();
    std::string get_publisher();
    std::string get_encodedBy();
    std::string get_artworkURL();
    std::string get_trackID();
    std::string get_mrl();

private:
    std::string get_meta( libvlc_meta_t e_meta );

protected:
    virtual vlc::media get_media() = 0;

private:
    FBVLCWeakPtr m_plugin;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCCurrentMediaDescAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCCurrentMediaDescAPI )
class FBVLCCurrentMediaDescAPI : public FBVLCMediaDescAPI
{
public:
    FBVLCCurrentMediaDescAPI( const FBVLCPtr& plugin )
        : FBVLCMediaDescAPI( plugin ) {}

protected:
    virtual vlc::media get_media();
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCMediaMediaDescAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCMediaMediaDescAPI )
class FBVLCMediaMediaDescAPI : public FBVLCMediaDescAPI
{
public:
    FBVLCMediaMediaDescAPI( const FBVLCPtr& plugin, const vlc::media& );
    ~FBVLCMediaMediaDescAPI();

protected:
    virtual vlc::media get_media();

private:
    vlc::media m_media;
};

////////////////////////////////////////////////////////////////////////////
/// FBVLCAPI
////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR( FBVLCAPI )
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
    FBVLCAPI( const FBVLCPtr& plugin, const FB::BrowserHostPtr& host)
        : m_plugin( plugin ), m_host( host )
    {
        // Read-only property
        registerProperty( "version",
                          make_property( this,
                                         &FBVLCAPI::get_version ) );
        registerProperty( "vlcVersion",
                          make_property( this,
                                         &FBVLCAPI::get_vlcVersion ) );
        registerProperty( "playing",
                          make_property( this,
                                         &FBVLCAPI::get_playing ) );
        registerProperty( "length",
                          make_property( this,
                                         &FBVLCAPI::get_length ) );

        registerProperty( "position",
                          make_property( this, &FBVLCAPI::get_position,
                                               &FBVLCAPI::set_position ) );
        registerProperty( "time",
                          make_property( this, &FBVLCAPI::get_time,
                                               &FBVLCAPI::set_time ) );
        registerProperty( "volume",
                          make_property( this, &FBVLCAPI::get_volume,
                                               &FBVLCAPI::set_volume ) );
        registerProperty( "bgcolor",
                          make_property( this, &FBVLCAPI::get_bgcolor,
                                               &FBVLCAPI::set_bgcolor ) );
        registerProperty( "fullscreen",
                          make_property( this, &FBVLCAPI::get_fullscreen,
                                               &FBVLCAPI::set_fullscreen)  );

        registerMethod( "play",             make_method( this, &FBVLCAPI::play ) );
        registerMethod( "pause",            make_method( this, &FBVLCAPI::pause ) );
        registerMethod( "togglePause",      make_method( this, &FBVLCAPI::togglePause ) );
        registerMethod( "stop",             make_method( this, &FBVLCAPI::stop ) );
        registerMethod( "toggleMute",       make_method( this, &FBVLCAPI::toggleMute ) );
        registerMethod( "toggleFullscreen", make_method( this, &FBVLCAPI::toggleFullscreen ) );

        registerAttribute( "libvlc_NothingSpecial", libvlc_NothingSpecial, true );
        registerAttribute( "libvlc_Opening",        libvlc_Opening,        true );
        registerAttribute( "libvlc_Buffering",      libvlc_Buffering,      true );
        registerAttribute( "libvlc_Playing",        libvlc_Playing,        true );
        registerAttribute( "libvlc_Paused",         libvlc_Paused,         true );
        registerAttribute( "libvlc_Stopped",        libvlc_Stopped,        true );
        registerAttribute( "libvlc_Ended",          libvlc_Ended,          true );
        registerAttribute( "libvlc_Error",          libvlc_Error,          true );
        registerProperty( "state",    make_property( this, &FBVLCAPI::get_state ) );

        m_audio = boost::make_shared<FBVLCAudioAPI>( plugin, m_host );
        registerProperty( "audio", make_property( this, &FBVLCAPI::get_audio ) );

        m_input = boost::make_shared<FBVLCInputAPI>( plugin, m_host );
        registerProperty( "input", make_property( this, &FBVLCAPI::get_input ) );

        m_playlist = boost::make_shared<FBVLCPlaylistAPI>( plugin, m_host );
        registerProperty( "playlist", make_property( this, &FBVLCAPI::get_playlist ) );

        m_subtitle = boost::make_shared<FBVLCSubtitleAPI>( plugin, m_host );
        registerProperty( "subtitle", make_property( this, &FBVLCAPI::get_subtitle ) );

        m_video = boost::make_shared<FBVLCVideoAPI>( plugin, m_host );
        registerProperty( "video", make_property( this, &FBVLCAPI::get_video ) );

        m_mediaDesc = boost::make_shared<FBVLCCurrentMediaDescAPI>( plugin );
        registerProperty( "mediaDescription", make_property( this, &FBVLCAPI::get_mediaDesc ) );

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

    std::string get_version();
    std::string get_vlcVersion();

    void play( const std::string& mrl );
    void pause();
    void togglePause();
    void stop();

    bool get_playing();

    double get_length();

    double get_position();
    void set_position( double );

    double get_time();
    void set_time( double );

    unsigned int get_volume();
    void set_volume( unsigned int );

    void toggleMute();

    std::string get_bgcolor();
    void set_bgcolor( const std::string& bg );

    bool get_fullscreen();
    void set_fullscreen( bool fs );

    int get_state();

    void toggleFullscreen();

    FBVLCAudioAPIWeakPtr     get_audio()     { return m_audio; }
    FBVLCInputAPIWeakPtr     get_input()     { return m_input; }
    FBVLCPlaylistAPIWeakPtr  get_playlist()  { return m_playlist; }
    FBVLCSubtitleAPIWeakPtr  get_subtitle()  { return m_subtitle; }
    FBVLCVideoAPIWeakPtr     get_video()     { return m_video; }
    FBVLCMediaDescAPIWeakPtr get_mediaDesc() { return m_mediaDesc; }

    /* async events from libvlc */
    FB_JSAPI_EVENT( MediaPlayerMediaChanged, 0, () );
    FB_JSAPI_EVENT( MediaPlayerNothingSpecial, 0, () );
    FB_JSAPI_EVENT( MediaPlayerOpening, 0, () );
    FB_JSAPI_EVENT( MediaPlayerBuffering, 1, ( float ) );
    FB_JSAPI_EVENT( MediaPlayerPlaying, 0, () );
    FB_JSAPI_EVENT( MediaPlayerPaused, 0, () );
    FB_JSAPI_EVENT( MediaPlayerForward, 0, () );
    FB_JSAPI_EVENT( MediaPlayerBackward, 0, () );
    FB_JSAPI_EVENT( MediaPlayerEncounteredError, 0, () );
    FB_JSAPI_EVENT( MediaPlayerEndReached, 0, () );
    FB_JSAPI_EVENT( MediaPlayerStopped, 0, () );

    FB_JSAPI_EVENT( MediaPlayerTimeChanged, 1, ( double ) );
    FB_JSAPI_EVENT( MediaPlayerPositionChanged, 1, ( float ) );
    FB_JSAPI_EVENT( MediaPlayerSeekableChanged, 1, ( bool ) );
    FB_JSAPI_EVENT( MediaPlayerPausableChanged, 1, ( bool ) );

private:
    FBVLCWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    FBVLCAudioAPIPtr            m_audio;
    FBVLCInputAPIPtr            m_input;
    FBVLCPlaylistAPIPtr         m_playlist;
    FBVLCSubtitleAPIPtr         m_subtitle;
    FBVLCVideoAPIPtr            m_video;
    FBVLCCurrentMediaDescAPIPtr m_mediaDesc;
};

#endif // H_FBVLCAPI
