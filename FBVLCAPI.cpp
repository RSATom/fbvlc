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

    p.set_channel(ch);
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
