/**********************************************************\

  Auto-generated FBVLCAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "FBVLCAPI.h"

////////////////////////////////////////////////////////////////////////////
/// FBVLCAudioAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCAudioAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

unsigned int FBVLCAudioAPI::get_count()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.track_count();
}

bool FBVLCAudioAPI::get_mute()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.is_muted();
}

void FBVLCAudioAPI::set_mute(bool m)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_mute(m);
}

unsigned int FBVLCAudioAPI::get_volume()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_volume();
}

void FBVLCAudioAPI::set_volume(unsigned int vol)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_volume(vol);
}

unsigned int FBVLCAudioAPI::get_track()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_track();
}

void FBVLCAudioAPI::set_track(unsigned int t)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_track(t);
}

unsigned int FBVLCAudioAPI::get_channel()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_channel();
}

void FBVLCAudioAPI::set_channel(unsigned int ch)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_channel( (libvlc_audio_output_channel_t) ch );
}

void FBVLCAudioAPI::toggleMute()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.toggle_mute();
}

std::string FBVLCAudioAPI::description(unsigned int trackID)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string track_name;

    libvlc_track_description_t* root_track_desc =
        libvlc_audio_get_track_description(p.get_mp());
    if( !root_track_desc )
        return track_name;

    unsigned int tc = p.track_count();
    if( tc && trackID < tc ) {
        libvlc_track_description_t* track_desc = root_track_desc;
        for(; trackID && track_desc ; --trackID ){
            track_desc = track_desc->p_next;
        }

        if ( track_desc && track_desc->psz_name ) {
            track_name = track_desc->psz_name;
        }
    }
    libvlc_track_description_list_release(root_track_desc);

    return track_name;
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCInputAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCInputAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

double FBVLCInputAPI::get_length()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return static_cast<double>(p.get_length());
}

double FBVLCInputAPI::get_fps()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_fps();
}

bool FBVLCInputAPI::get_hasVout()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.has_vout();
}

unsigned int FBVLCInputAPI::get_state()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_state();
}

double FBVLCInputAPI::get_position()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_position();
}

void FBVLCInputAPI::set_position(double pos)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_position(static_cast<float>(pos));
}

double FBVLCInputAPI::get_time()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return static_cast<double>(p.get_time());
}

void FBVLCInputAPI::set_time(double t)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.set_time(static_cast<libvlc_time_t>(t));
}

double FBVLCInputAPI::get_rate()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_rate();
}

void FBVLCInputAPI::set_rate(double r)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_rate(static_cast<float>(r));
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCPlaylistItemsAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCPlaylistItemsAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

unsigned int FBVLCPlaylistItemsAPI::get_count()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.items_count();
}

void FBVLCPlaylistItemsAPI::clear()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.clear_items();
}

bool FBVLCPlaylistItemsAPI::remove(unsigned int idx)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

   return p.delete_item(idx);
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCPlaylistAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCPlaylistAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

unsigned int FBVLCPlaylistAPI::get_itemCount()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.items_count();
}

bool FBVLCPlaylistAPI::get_isPlaying()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.is_playing();
}

int FBVLCPlaylistAPI::add(const std::string& mrl)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.add_item(mrl.c_str());
}

int FBVLCPlaylistAPI::addWithOptions(const std::string& mrl,
                                     const std::vector<std::string>& options)
{
    if( options.empty() )
        return add(mrl);

    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::vector<const char*> char_opts;
    for( unsigned int i=0; i<options.size(); ++i ) {
        char_opts.push_back(options[i].c_str());
    }

    return p.add_item(mrl.c_str(), char_opts.size(), &char_opts[0]);
}

void FBVLCPlaylistAPI::play()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.play();
}

bool FBVLCPlaylistAPI::playItem(unsigned int idx)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.play(idx);
}

void FBVLCPlaylistAPI::togglePause()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    if ( p.is_playing() ) p.pause();
    else p.play();
}

void FBVLCPlaylistAPI::stop()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.stop();
}

void FBVLCPlaylistAPI::next()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.next();
}

void FBVLCPlaylistAPI::prev()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.prev();
}

void FBVLCPlaylistAPI::clear()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.clear_items();
}

bool FBVLCPlaylistAPI::removeItem(unsigned int idx)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.delete_item(idx);
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCSubtitleAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCSubtitleAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

unsigned int FBVLCSubtitleAPI::get_count()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_spu_count(p.get_mp());
}

int FBVLCSubtitleAPI::get_track()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_spu(p.get_mp());
}

void FBVLCSubtitleAPI::set_track(unsigned int t)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_spu(p.get_mp(), t);
}

std::string FBVLCSubtitleAPI::description(unsigned int sID)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string s_name;

    libvlc_track_description_t* root_s_desc =
        libvlc_video_get_spu_description(p.get_mp());
    if( !root_s_desc )
        return s_name;

    unsigned int sc = libvlc_video_get_spu_count(p.get_mp());
    if( sc && sID < sc ) {
        libvlc_track_description_t* s_desc = root_s_desc;
        for(; sID && s_desc ; --sID ){
            s_desc = s_desc->p_next;
        }

        if ( s_desc && s_desc->psz_name ) {
            s_name = s_desc->psz_name;
        }
    }
    libvlc_track_description_list_release(root_s_desc);

    return s_name;
}

////////////////////////////////////////////////////////////////////////////
/// positions
////////////////////////////////////////////////////////////////////////////
const char* positions [] = {
    "center",        // 0
    "left",          // 1
    "right",         // 2
    0,               // 3
    "top",           // 4
    "top-left",      // 5
    "top-right",     // 6
    0,               // 7
    "bottom",        // 8
    "bottom-left",   // 9
    "bottom-right",  //10
};

inline std::string get_position_by_id(unsigned int id)
{
    unsigned int p_size = sizeof(positions)/sizeof(positions[0]);
    if( id < p_size && positions[id] ) {
        return positions[id];
    }
    else return std::string();
}

int get_id_by_position(const std::string& pos)
{
    int p_size = sizeof(positions)/sizeof(positions[0]);
    for(int i=0; i<p_size; ++i) {
        if( positions[i] && pos == positions[i] )
            return i;
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCMarqueeAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCMarqueeAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

std::string FBVLCMarqueeAPI::get_text()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string text;
    char* t = libvlc_video_get_marquee_string(p.get_mp(), libvlc_marquee_Text);
    if ( t )
        text = t;

    return text;
}

void FBVLCMarqueeAPI::set_text(const std::string& t)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_marquee_string(p.get_mp(), libvlc_marquee_Text, t.c_str());
}

std::string FBVLCMarqueeAPI::get_position()
{
    int p = get_marquee_int(libvlc_marquee_Position);
    return get_position_by_id(p);
}

void FBVLCMarqueeAPI::set_position(const std::string& position)
{
    int p = get_id_by_position(position);
    set_marquee_int(libvlc_marquee_Position, p);
}

int FBVLCMarqueeAPI::get_marquee_int(libvlc_video_marquee_option_t o)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_marquee_int(p.get_mp(), o);
}

void FBVLCMarqueeAPI::set_marquee_int(libvlc_video_marquee_option_t o, int i)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_marquee_int(p.get_mp(), o, i);
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCLogoAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCLogoAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

std::string FBVLCLogoAPI::get_position()
{
    int p = get_logo_int(libvlc_logo_position);
    return get_position_by_id(p);
}

void FBVLCLogoAPI::set_position(const std::string& position)
{
    int p = get_id_by_position(position);
    set_logo_int(libvlc_logo_position, p);
}

void FBVLCLogoAPI::file(const std::string& f)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_logo_string(p.get_mp(), libvlc_logo_file, f.c_str());
}

int FBVLCLogoAPI::get_logo_int(libvlc_video_logo_option_t o)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_logo_int(p.get_mp(), o);
}

void FBVLCLogoAPI::set_logo_int(libvlc_video_logo_option_t o, int i)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_logo_int(p.get_mp(), o, i);
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCDeinterlaceAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCDeinterlaceAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

void FBVLCDeinterlaceAPI::enable(const std::string& mode)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_deinterlace(p.get_mp(), mode.c_str());
}

void FBVLCDeinterlaceAPI::disable()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_deinterlace(p.get_mp(), "");
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCVideoAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCVideoAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

unsigned int FBVLCVideoAPI::get_width()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    unsigned x=0, y=0;
    libvlc_video_get_size(p.get_mp(), 0, &x, &y);

    return x;
}

unsigned int FBVLCVideoAPI::get_height()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    unsigned x=0, y=0;
    libvlc_video_get_size(p.get_mp(), 0, &x, &y);

    return y;
}

bool FBVLCVideoAPI::get_fullscreen()
{
    FBVLCPtr plg = getPlugin();

    return plg->is_fullscreen();
}

void FBVLCVideoAPI::set_fullscreen(bool fs)
{
    FBVLCPtr plg = getPlugin();

    return plg->set_fullscreen(fs);
}

void FBVLCVideoAPI::toggleFullscreen()
{
    FBVLCPtr plg = getPlugin();

    plg->toggle_fullscreen();
}

std::string FBVLCVideoAPI::get_aspectRatio()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string aspectRatio;
    char* ar = libvlc_video_get_aspect_ratio(p.get_mp());
    if ( ar )
        aspectRatio = ar;
    free(ar);

    return aspectRatio;
}

void FBVLCVideoAPI::set_aspectRatio(std::string& ar)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_aspect_ratio(p.get_mp(), ar.c_str());
}

int FBVLCVideoAPI::get_subtitle()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_spu(p.get_mp());
}

void FBVLCVideoAPI::set_subtitle(unsigned int t)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_spu(p.get_mp(), t);
}

std::string FBVLCVideoAPI::get_crop()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    std::string crop;
    char* c = libvlc_video_get_crop_geometry(p.get_mp());
    if ( c )
        crop = c;
    free(c);

    return crop;
}

void FBVLCVideoAPI::set_crop(std::string& c)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_video_set_crop_geometry(p.get_mp(), c.c_str());
}

int FBVLCVideoAPI::get_teletext()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_get_teletext(p.get_mp());
}

void FBVLCVideoAPI::set_teletext(unsigned int t)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return libvlc_video_set_teletext(p.get_mp(), t);
}

void FBVLCVideoAPI::toggleTeletext()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_toggle_teletext(p.get_mp());
}

////////////////////////////////////////////////////////////////////////////
/// FBVLCMediaDescAPI
////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCMediaDescAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

std::string FBVLCMediaDescAPI::get_meta(libvlc_meta_t e_meta)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    libvlc_media_t * p_media = libvlc_media_player_get_media(p.get_mp());
    const char* info = p_media ? libvlc_media_get_meta(p_media, e_meta) : 0;
    return info;
}

std::string FBVLCMediaDescAPI::get_title()
{
    return get_meta(libvlc_meta_Title);
}

std::string FBVLCMediaDescAPI::get_artist()
{
    return get_meta(libvlc_meta_Artist);
}

std::string FBVLCMediaDescAPI::get_genre()
{
    return get_meta(libvlc_meta_Genre);
}

std::string FBVLCMediaDescAPI::get_copyright()
{
    return get_meta(libvlc_meta_Copyright);
}

std::string FBVLCMediaDescAPI::get_album()
{
    return get_meta(libvlc_meta_Album);
}

std::string FBVLCMediaDescAPI::get_trackNumber()
{
    return get_meta(libvlc_meta_TrackNumber);
}

std::string FBVLCMediaDescAPI::get_description()
{
    return get_meta(libvlc_meta_Description);
}

std::string FBVLCMediaDescAPI::get_rating()
{
    return get_meta(libvlc_meta_Rating);
}

std::string FBVLCMediaDescAPI::get_date()
{
    return get_meta(libvlc_meta_Date);
}

std::string FBVLCMediaDescAPI::get_setting()
{
    return get_meta(libvlc_meta_Setting);
}

std::string FBVLCMediaDescAPI::get_URL()
{
    return get_meta(libvlc_meta_URL);
}

std::string FBVLCMediaDescAPI::get_language()
{
    return get_meta(libvlc_meta_Language);
}

std::string FBVLCMediaDescAPI::get_nowPlaying()
{
    return get_meta(libvlc_meta_NowPlaying);
}

std::string FBVLCMediaDescAPI::get_publisher()
{
    return get_meta(libvlc_meta_Publisher);
}

std::string FBVLCMediaDescAPI::get_encodedBy()
{
    return get_meta(libvlc_meta_EncodedBy);
}

std::string FBVLCMediaDescAPI::get_artworkURL()
{
    return get_meta(libvlc_meta_ArtworkURL);
}

std::string FBVLCMediaDescAPI::get_trackID()
{
    return get_meta(libvlc_meta_TrackID);
}

///////////////////////////////////////////////////////////////////////////////
/// @fn FBVLCPtr FBVLCAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read-only property version
std::string FBVLCAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

std::string FBVLCAPI::get_vlcVersion()
{
    return libvlc_get_version();
}

void FBVLCAPI::play(const std::string& mrl)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.clear_items();

    int item = p.add_item(mrl.c_str(), 0, 0);
    if( item >= 0) {
        p.play(item);
    }
}

void FBVLCAPI::togglePause()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    if ( p.is_playing() ) p.pause();
    else p.play();
}

void FBVLCAPI::stop()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.stop();
    p.clear_items();
}

void FBVLCAPI::toggleMute()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.toggle_mute();
}

bool FBVLCAPI::get_playing()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.is_playing();
}

double FBVLCAPI::get_length()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return static_cast<double>(p.get_length());
}

double FBVLCAPI::get_position()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_position();
}

void FBVLCAPI::set_position(double pos)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_position(static_cast<float>(pos));
}

double FBVLCAPI::get_time()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return static_cast<double>(p.get_time());
}

void FBVLCAPI::set_time(double t)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_time(static_cast<libvlc_time_t>(t));
}

unsigned int FBVLCAPI::get_volume()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_volume();
}

void FBVLCAPI::set_volume(unsigned int v)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.set_volume(v);
}

std::string FBVLCAPI::get_bgcolor()
{
    FBVLCPtr plg = getPlugin();
    vlc_player_options& o = plg->get_options();

    return o.get_bg_color();
}

void FBVLCAPI::set_bgcolor(const std::string& bg)
{
    FBVLCPtr plg = getPlugin();
    vlc_player_options& o = plg->get_options();

    o.set_bg_color(bg);
}

int FBVLCAPI::get_state()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    return p.get_state();
};

bool FBVLCAPI::get_fullscreen()
{
    FBVLCPtr plg = getPlugin();

    return plg->is_fullscreen();
}

void FBVLCAPI::set_fullscreen(bool fs)
{
    FBVLCPtr plg = getPlugin();

    return plg->set_fullscreen(fs);
}

void FBVLCAPI::toggleFullscreen()
{
    FBVLCPtr plg = getPlugin();

    plg->toggle_fullscreen();
}
